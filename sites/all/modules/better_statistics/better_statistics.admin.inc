<?php

/**
 * @file
 * Admin and config code for the Better Statistics module.
 */


/**
 * Makes alterations to the core Statistics configuration form.
 */
function _better_statistics_form_statistics_settings_form_alter(&$form, &$form_state, $form_id) {
  // Alter the access log settings to indicate a requirement.
  $log_description = &$form['access']['statistics_enable_access_log']['#description'];
  $log_description .= ' ' . t('Also required by the Better Statistics module.');

  $form['access']['#weight'] = -10;

  // Create a fieldset for data collection settings.
  $form['better_statistics'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Access log data'),
    '#description' => t('Select the data you would like to collect on each page request. Note that unchecking a field below will permanently delete all data collected for that field.'),
    '#weight' => -8,
    '#tree' => TRUE,
    // Only show this fieldset if the accesslog is enabled.
    '#states' => array(
      'visible' => array(
        ':input[name="statistics_enable_access_log"]' => array('checked' => TRUE),
      ),
    ),
  );

  // Get all fields provided by core.
  $fields_modules = array();
  $fields_modules['statistics'] = better_statistics_get_default_fields();

  // Get a list of all modules implementing our hook and their fields.
  $fields_modules += _better_statistics_get_custom_fields_by_module();

  // Get currently active fields from the active store.
  $current = variable_get('better_statistics_fields', better_statistics_get_default_fields());

  // Create a series of checkboxes with all declared fields.
  foreach ($fields_modules as $module => $fields) {
    // Get the module name for display.
    $module_info = system_get_info('module', $module);

    // Get the fields and current defaults for this module.
    $field_set = array();
    $defaults = array();
    foreach ($fields as $field => $data) {
      // If a title is explicitly declared, use it.
      if (isset($data['views_field']['title'])) {
        $title = '<strong>' . t($data['views_field']['title']) . '</strong>';
        $field_set[$field] = $title;
      }
      else {
        $field_set[$field] = '<strong>' . $field . '</strong>';
      }

      // If help text is explicitly declared, use it.
      if (isset($data['views_field']['help'])) {
        $field_set[$field] .= ': ' . t($data['views_field']['help']);
      }
      // If not, but if a schema description is declared, use it.
      elseif (isset($data['schema']['description'])) {
        $field_set[$field] .= ': ' . t($data['schema']['description']);
      }

      // Check whether this field is currently active.
      if (isset($current[$field])) {
        $defaults[$field] = $field;
      }
    }

    // Special case: for now, don't allow disabling core accesslog fields.
    $disabled = $module == 'statistics' ? TRUE : FALSE;

    // Special case: Better Statistics started by simply adding its own fields
    // via the regular schema API. We should maintain those defaults if they're
    // actually reflected in the database.
    // @todo This should be removed once we hit a 1.2 or 1.3 release.
    if ($module == 'better_statistics' && empty($defaults)) {
      if (db_field_exists('accesslog', 'cache')) {
        $defaults['cache'] = 'cache';
      }
      if (db_field_exists('accesslog', 'user_agent')) {
        $defaults['user_agent'] = 'user_agent';
      }
    }

    // Make a collapsible fieldset for the module.
    $form['better_statistics'][$module] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => check_plain($module_info['name']),
    );
    // Create checkboxes for all fields detected for this module.
    $form['better_statistics'][$module]['fields'] = array(
      '#type' => 'checkboxes',
      '#options' => $field_set,
      '#disabled' => $disabled,
      '#default_value' => $defaults,
    );
  }

  $form['access_log_restrictions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Access log restrictions'),
    '#description' => t('Define restrictions on when page requests are logged in the access log. As an example, you may want to disable logging in admin areas or, only log access for specific user roles.'),
    '#weight' => -6,
    // Only show this fieldset if the accesslog is enabled.
    '#states' => array(
      'visible' => array(
        ':input[name="statistics_enable_access_log"]' => array('checked' => TRUE),
      ),
    ),
  );
  // Cache-based restrictions reference.
  if (variable_get('cache', 0)) {
    $form['access_log_restrictions']['caching'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Cache'),
    );
    $form['access_log_restrictions']['caching']['log_cached_status'] = array(
      '#markup' => t('Tracking of page requests served from cache is currently !log_cached_status. Visit !the_performance_configuration_page to change settings.', array(
        '!log_cached_status' => '<strong>' . (variable_get('statistics_access_log_restrictions_cache', TRUE) ? t('enabled') : t('disabled')) . '</strong>',
        '!the_performance_configuration_page' => l(t('the performance configuration page'), 'admin/config/development/performance'),
      )),
    );
  }
  // Page-based restrictions.
  $form['access_log_restrictions']['pages'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Pages'),
  );
  $form['access_log_restrictions']['pages']['statistics_access_log_restrictions_page'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('All pages except those listed'),
      1 => t('Only the listed pages'),
    ),
    '#title' => t('Log requests on specific pages'),
    '#default_value' => variable_get('statistics_access_log_restrictions_page', 0),
  );
  $form['access_log_restrictions']['pages']['statistics_access_log_restrictions_pages'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#default_value' => variable_get('statistics_access_log_restrictions_pages', ''),
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
      '%blog' => 'blog',
      '%blog-wildcard' => 'blog/*',
      '%front' => '<front>',
    )),
  );
  // User-based restrictions.
  $form['access_log_restrictions']['users'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Users'),
    '#group' => 'restrictions_settings',
  );
  $form['access_log_restrictions']['users']['statistics_access_log_restrictions_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => user_roles(),
    '#title' => t('Log requests for specific roles'),
    '#default_value' => variable_get('statistics_access_log_restrictions_roles', array()),
    '#description' => t('Log requests only for the selected role(s). If you select no roles, statistics will be collected for all users.'),
  );
  $form['access_log_restrictions']['users']['statistics_access_log_restrictions_dnt'] = array(
    '#type' => 'checkbox',
    '#title' => t('Respect the "Do Not Track" header'),
    '#default_value' => variable_get('statistics_access_log_restrictions_dnt', FALSE),
    '#description' => t('When checked, statistics will not be collected for users who have "do not track" enabled in their browsers.'),
  );

  // Add a submit handler to handle schema changes as a result of changes here.
  // Fire before the system settings; we don't want it to save variables.
  array_unshift($form['#submit'], 'better_statistics_settings_form_submit');
}


/**
 * Makes alterations to the core site performance settings configuration form.
 */
function _better_statistics_form_system_performance_settings_alter(&$form, &$form_state, $form_id) {
  $form['caching']['statistics_access_log_restrictions_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log access statistics for pages served from cache'),
    '#description' => t('Logging access statistics on cached page requests can negatively impact performance and scalability.'),
    '#default_value' => variable_get('statistics_access_log_restrictions_cache', TRUE),
    // Only show this field if caching is enabled.
    '#states' => array(
      'visible' => array(
        ':input[name="cache"]' => array('checked' => TRUE),
      ),
    ),
  );
}


/**
 * Submit handler for Better Statistics configuration settings.
 */
function _better_statistics_settings_form_submit($form, &$form_state) {
  // Get all declared fields.
  $declared = _better_statistics_get_custom_fields_by_module();

  // Compare the declared fields to what was submitted in the form.
  $customizations = array();
  foreach ($declared as $module => $fields) {
    foreach ($fields as $name => $field) {
      if ($form_state['values']['better_statistics'][$module]['fields'][$name]) {
        $customizations[$name] = $field;
      }
    }
  }

  // Get various combinations of fields for schema comparisons.
  $defaults = better_statistics_get_default_fields();
  $default_and_custom = $defaults + $customizations;
  $active = variable_get('better_statistics_fields', $defaults);

  // Compare the fields we turned up above to what currently exists.
  $fields_added = array_keys(array_diff_key($default_and_custom, $active));
  better_statistics_enable_fields($fields_added);
  $fields_removed = array_keys(array_diff_key($active, $default_and_custom));
  better_statistics_disable_fields($fields_removed);

  // Ensure Better Statistics data isn't unintentionally processed.
  unset($form_state['values']['better_statistics']);
}


/**
 * Enables a list of statistics fields.
 *
 * @param $fields
 *   An array of field names to enable.
 *
 * @return
 *   An array of statistics fields that were enabled.
 */
function better_statistics_enable_fields($fields) {
  // Get all declared and active fields.
  $declared = _better_statistics_get_custom_fields_by_module();
  $active = variable_get('better_statistics_fields', better_statistics_get_default_fields());
  $successfully_enabled = array();

  // Accept a single field enable.
  if (!is_array($fields)) {
    $fields = array($fields);
  }

  // Load field schema data for all fields being enabled.
  $fields_added = array();
  foreach ($fields as $name) {
    foreach ($declared as $module => $module_fields) {
      if (isset($module_fields[$name])) {
        $fields_added[$name] = $module_fields[$name];
      }
    }
  }

   // Loop through each field.
  foreach ($fields_added as $field => $data) {
    // Verify the field is valid.
    $schema_set = isset($data['schema']) ? is_array($data['schema']) : FALSE;
    $callable = isset($data['callback']) ? is_callable($data['callback']) : FALSE;
    $field_exists = db_field_exists('accesslog', $field);

    if ($schema_set && $callable && !$field_exists) {
      // Add the field to the database.
      db_add_field('accesslog', $field, $data['schema']);

      // Add the field to the active store.
      $active += array($field => $data);

      // Log the field addition in watchdog.
      watchdog('better statistics', 'Successfully added field %field to accesslog.', array(
        '%field' => $field,
      ), WATCHDOG_NOTICE);

      // Add key to the list of fields successfully added.
      $successfully_enabled[] = $field;
    }
    // Special case: support for legacy default field additions by Better
    // Statistics module. If this is detected to be a field addition but the
    // field already exists, we just need to add it to the active store.
    elseif ($field_exists) {
      // Add the field to the active store.
      $active += array($field => $data);

      // Add key to the list of fields successfully added.
      $successfully_enabled[] = $field;
    }
    else {
      // Alert the failure.
      watchdog('better statistics', 'Unable to add field %field to accesslog.', array(
        '%field' => $field,
      ), WATCHDOG_WARNING);
    }
  }

  // Save the active store with any changes.
  variable_set('better_statistics_fields', $active);

  // It can be convenient to call the field update function after configuration.
  _better_statistics_update_fields();

  // Clear the Views data cache so fields are registered.
  if (module_exists('views')) {
    cache_clear_all('views_data:', 'cache_views', TRUE);
  }

  return $successfully_enabled;
}


/**
 * Disables a list of statistics fields.
 *
 * @param $fields
 *   An array of statistics fields to be disabled.
 *
 * @return
 *   An array of the statistics fields that were disabled.
 */
function better_statistics_disable_fields($fields) {
  // Get all declared and active fields.
  $declared = _better_statistics_get_custom_fields_by_module();
  $active = variable_get('better_statistics_fields', better_statistics_get_default_fields());
  $successfully_disabled = array();

  // Accept a single field enable.
  if (!is_array($fields)) {
    $fields = array($fields);
  }

  // Load field schema data for all fields being enabled.
  $fields_removed = array();
  foreach ($fields as $name) {
    foreach ($declared as $module => $module_fields) {
      if (isset($module_fields[$name])) {
        $fields_removed[$name] = $module_fields[$name];
      }
    }
  }

  // Loop through each missing field.
  foreach ($fields_removed as $field => $data) {
    // Verify the field exists.
    if (db_field_exists('accesslog', $field)) {
      // Drop the field from the database.
      db_drop_field('accesslog', $field);

      // Remove the field from the active store.
      unset($active[$field]);

      // Log the field removal in watchdog.
      watchdog('better statistics', 'Successfully dropped field %field from accesslog.', array(
        '%field' => $field,
      ), WATCHDOG_NOTICE);

      // Add key to the list of fields successfully removed.
      $successfully_disabled[] = $field;
    }
  }

  // Save the active store with any changes.
  variable_set('better_statistics_fields', $active);

  // It can be convenient to call the field update function after configuration.
  _better_statistics_update_fields();

  // Clear the Views data cache so fields are registered.
  if (module_exists('views')) {
    cache_clear_all('views_data:', 'cache_views', TRUE);
  }

  return $successfully_disabled;
}

/**
 * Determines whether or not accesslog fields should be altered, and if so,
 * performs any necessary database alterations and re-saves the declared
 * fields to the active store variable.
 *
 * It is absolutely necessary that this function does all sanity checks because
 * if not, it's possible for our hook_exit() call to insert data into
 * non-existent fields.
 *
 * This function is also necessary to ensure that our schema alter is always in
 * line with what's actually declared in the database.
 */
function _better_statistics_update_fields() {
  // Attempt to get all fields, including customizations from other modules.
  $active = variable_get('better_statistics_fields', FALSE);
  $customizations = _better_statistics_get_custom_fields_by_module();
  $available_fields = array_keys(better_statistics_get_default_fields());

  // There's no reason for this to run if no custom fields are installed.
  if (!$active) {
    return;
  }

  // Write through updates to the non-schema portions of custom fields; also
  // check for, perform, and write through schema updates.
  foreach ($customizations as $module => $data) {
    foreach ($data as $field => $field_data) {
      // Only check for differences in pre-existing fields in the active store.
      if (isset($active[$field])) {
        // Check that the new callback is callable and write through.
        if (is_callable($field_data['callback'])) {
          $active[$field]['callback'] = $field_data['callback'];
        }

        // Write through Views API changes.
        $active[$field]['views_field'] = $field_data['views_field'];

        // Write through the location of the callback.
        if (isset($field_data['_file'])) {
          $active[$field]['_file'] = $field_data['_file'];
        }

        // Check for updates to the schema.
        if ($active[$field]['schema'] != $field_data['schema']) {
          try {
            // Change the schema.
            db_change_field('accesslog', $field, $field, $field_data['schema']);

            // Write through the change to the active store.
            $active[$field]['schema'] = $field_data['schema'];

            // Log the field change in watchdog.
            watchdog('better statistics', 'Successfully changed field %field in the accesslog.', array(
              '%field' => $field,
            ), WATCHDOG_NOTICE);
          }
          catch (Exception $e) {
            $module_info = system_get_info('module', $module);
            $message = filter_xss_admin('<em>Error</em>: Failed to update the %field field in the access log. Please make sure you are using the latest version of the @module module.');
            $options = array(
              '%field' => $field,
              '@module' => $module_info['name'],
            );

            // Set a message notifying the user.
            drupal_set_message(t($message, $options), 'error');

            // Log the failed attempt in watchdog and add more details.
            $message .= filter_xss_admin('<br /><br /><strong>Error message:</strong><br />@error');
            $options['@error'] = $e->getMessage();
            watchdog('better statistics', $message, $options, WATCHDOG_ERROR);
          }
        }
      }

      // Save this field as an available field.
      $available_fields[] = $field;
    }
  }

  // Check for fields in the active store that no longer exist.
  foreach ($active as $field => $data) {
    if (!in_array($field, $available_fields)) {
      $message = 'A recent module update has invalidated the %field field in the access log. No data has been removed at this time, but all data in the field will be lost next time Better Statistics settings are updated.';
      $options = array('%field' => $field);
      drupal_set_message(t($message, $options), 'warning');
      watchdog('better statistics', $message, $options, WATCHDOG_WARNING);
    }
  }

  // Save the active store with any changes.
  variable_set('better_statistics_fields', $active);

  // Save off a list of active inc files to be loaded.
  $active_incs = array();
  foreach (_better_statistics_include_handlers() as $module => $api_info) {
    $active_incs[] = $api_info['file_required'];
  }
  variable_set('better_statistics_active_incs', $active_incs);
}


/**
 * Returns arrays of fields keyed by the module that declares them. In addition,
 * this function will attempt to apply sensible views handlers. This should be
 * the only function used to get declared fields.
 *
 * @return
 *   Arrays of declared statistics fields keyed by their declaring module.
 */
function _better_statistics_get_custom_fields_by_module() {
  $declared = array();

  // Load all Statistics API inc files.
  $api_info = _better_statistics_include_handlers();

  foreach (module_implements('better_statistics_fields') as $module) {
    $fields = module_invoke($module, 'better_statistics_fields');

    foreach ($fields as $field => &$data) {
      // Try to provide a default title.
      if (!isset($data['views_field']['title'])) {
        $data['views_field']['title'] = $field;
      }

      // Try to provide a default help text.
      if (!isset($data['views_field']['help'])) {
        $data['views_field']['help'] = isset($data['schema']['description']) ? $data['schema']['description'] : '';
      }

      // Unless explicitly told not to, make our best guesses on Views handlers.
      if ($data['views_field']) {
        $guesses = _better_statistics_get_views_handlers($data['schema']);
        if ($guesses) {
          $data['views_field'] += $guesses;
        }
        else {
          $data['views_field'] = FALSE;
        }
      }

      // Include the path to the file containing the API callback. If this isn't
      // set, the callback is available anywhere Drupal is bootstrapped.
      if (isset($api_info[$module]['file_required'])) {
        $data['_file'] = $api_info[$module]['file_required'];
      }
    }

    // Return the fields, now with Views API defaults, keyed by the module.
    $declared[$module] = $fields;
  }

  return $declared;
}


/**
 * Returns a best guess on which Views handlers should be used based on a
 * provided field schema.
 *
 * @param $schema
 *   An array representing the field's schema.
 *
 * @return
 *   An array of views handlers.
 */
function _better_statistics_get_views_handlers($schema) {
  $handlers = array();

  // Define some straightforward string handlers.
  $string_handlers = array(
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Define some straightforward numeric handlers.
  $numeric_handlers = array(
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  switch ($schema['type']) {
    case 'serial':
    case 'int':
    case 'float':
    case 'numeric':
      $handlers = $numeric_handlers;
      break;

    case 'varchar':
    case 'text':
      $handlers = $string_handlers;
      break;

    case 'blob':
      $handlers = FALSE;
      break;
  }

  return $handlers;
}


/**
 * Loads all inc files declared using the Statistics API.
 *
 * This is almost identical to ctools_plugin_api_include(), but modified a bit
 * to return file inclusion data.
 *
 * @return
 *   An array containing the API information, including the actual files that
 *   each module declares.
 */
function _better_statistics_include_handlers($reset = FALSE) {
  static $finished = FALSE;

  // Ensure this only runs once.
  if ($finished && !$reset) {
    return $finished;
  }

  // Check for ctools; this dependency was added after the initial relase.
  if (!module_exists('ctools')) {
    drupal_set_message(t('Better Statistics requires the ctools module. Please install and enable ctools.'), 'warning');
    return array();
  }

  ctools_include('plugins');
  $info = ctools_plugin_api_info('better_statistics', 'statistics', BETTER_STATISTICS_API_MIN_VERSION, BETTER_STATISTICS_API_VERSION);
  foreach ($info as $module => &$plugin_info) {
    if (!isset($already_done['better_statistics']['statistics'][$module])) {
      if (isset($plugin_info['statistics file'])) {
        $file = $plugin_info['statistics file'];
      }
      elseif (isset($plugin_info['file'])) {
        $file = $plugin_info['file'];
      }
      else {
        $file = "$module.statistics.inc";
      }

      if (file_exists(DRUPAL_ROOT . "/$plugin_info[path]/$file")) {
        require_once DRUPAL_ROOT . "/$plugin_info[path]/$file";
        $plugin_info['file_required'] = "$plugin_info[path]/$file";
      }
      elseif (file_exists(DRUPAL_ROOT . "/$file")) {
        require_once DRUPAL_ROOT . "/$file";
        $plugin_info['file_required'] = "$file";
      }
      $already_done['better_statistics']['statistics'][$module] = TRUE;
    }
  }

  $finished = $info;
  return $finished;
}


/**
 * Displays details of recent page accesses.
 *
 * Replacement of core 'statistics_access_log' callback.
 */
function better_statistics_access_log($aid) {
  $access = db_query('SELECT a.*, u.name FROM {accesslog} a LEFT JOIN {users} u ON a.uid = u.uid WHERE aid = :aid', array(':aid' => $aid))->fetch();
  if ($access) {
    $rows[] = array(
      array('data' => t('URL'), 'header' => TRUE),
      l(url($access->path, array('absolute' => TRUE)), $access->path)
    );
    // It is safe to avoid filtering $access->title through check_plain because
    // it comes from drupal_get_title().
    $rows[] = array(
      array('data' => t('Title'), 'header' => TRUE),
      $access->title
    );
    $rows[] = array(
      array('data' => t('Referrer'), 'header' => TRUE),
      ($access->url ? l($access->url, $access->url) : '')
    );
    $rows[] = array(
      array('data' => t('Date'), 'header' => TRUE),
      format_date($access->timestamp, 'long')
    );
    $rows[] = array(
      array('data' => t('User'), 'header' => TRUE),
      theme('username', array('account' => $access))
    );
    $rows[] = array(
      array('data' => t('Hostname'), 'header' => TRUE),
      check_plain($access->hostname)
    );
    $rows[] = array(
      array('data' => t('Page loading time (msec)'), 'header' => TRUE),
      check_plain($access->timer)
    );

    unset(
      $access->name,
      $access->aid,
      $access->sid,
      $access->title,
      $access->path,
      $access->url,
      $access->hostname,
      $access->uid,
      $access->timer,
      $access->timestamp
    );

    $fields = variable_get('better_statistics_fields', better_statistics_get_default_fields());
    foreach ($access as $field => $data) {
      $header = isset($fields[$field]['views_field']['title']) ? t($fields[$field]['views_field']['title']) : $field;
      $rows[] = array(
        array(
          'data' => $header,
          'header' => TRUE,
        ),
        $data ? check_plain($data) : '&nbsp',
      );
    }

    $build['statistics_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
    );
    return $build;
  }
  else {
    drupal_not_found();
  }
}
