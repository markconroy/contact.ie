<?php

/**
 * @file
 * Statistics API functions and hooks for the Better Statistics module.
 */


/**
 * Implements hook_better_statistics_fields().
 */
function better_statistics_better_statistics_fields() {
  $fields = array();

  // Pass all user-facing strings through t(), but always use English when first
  // declaring fields. They will be run through t() normally on output.
  $en = array('langcode' => 'en');

  // Declare a cache status field.
  $fields['cache'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 128,
      'not null' => FALSE,
      'description' => 'Cache hit, miss, or not applicable.',
    ),
    'callback' => 'better_statistics_get_field_value',
    'views_field' => array(
      'title' => t('Cache status', array(), $en),
      'help' => t('The cache status of the page (HIT, MISS, or NULL).', array(), $en),
    ),
  );

  // Declare a user agent field.
  $fields['user_agent'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      'description' => 'User-agent string used on the request.',
    ),
    'callback' => 'better_statistics_get_field_value',
    'views_field' => array(
      'title' => t('User-agent', array(), $en),
      'help' => t('User-agent string of the user who visited your page.', array(), $en),
    ),
  );

  // Declare a peak memory field.
  $fields['peak_memory'] = array(
    'schema' => array(
      'type' => 'int',
      'size' => 'normal',
      'not null' => TRUE,
      'default' => 0,
      'unsigned' => TRUE,
      'description' => 'Peak memory in bytes allocated for the request.',
    ),
    'callback' => 'memory_get_peak_usage',
    'views_field' => array(
      'title' => t('Peak memory', array(), $en),
      'help' => t('Size in bytes of the peak memory allocated for the request.', array(), $en),
    ),
  );

  return $fields;
}


/**
 * Returns a value to be inserted into the accesslog based on a field name
 * provided. This handles Drupal Core's values as well as our own.
 *
 * @param $field
 *   The name of the field for which to return data.
 *
 * @return
 *   The data to be inserted into the accesslog for the provided field.
 */
function better_statistics_get_field_value($field) {
  switch ($field) {
    case 'title':
      return truncate_utf8(strip_tags(drupal_get_title()), 255);

    case 'path':
      return truncate_utf8($_GET['q'], 255);

    case 'url':
      return isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : '';

    case 'hostname':
      return ip_address();

    case 'uid':
      global $user;
      return $user->uid;

    case 'sid':
      return session_id();

    case 'timer':
      return (int) timer_read('page');

    case 'timestamp':
      return REQUEST_TIME;

    case 'cache':
      $cached = NULL;
      $cache_status = better_statistics_served_from_cache();
      if ($cache_status === TRUE) {
        $cached = 'HIT';
      }
      elseif ($cache_status === FALSE) {
        $cached = 'MISS';
      }
      return $cached;

    case 'user_agent':
      return isset($_SERVER['HTTP_USER_AGENT']) ? truncate_utf8($_SERVER['HTTP_USER_AGENT'], 255) : '';
  }
}


/**
 * Implements hook_better_statistics_prelog().
 *
 * Better Statistics provides inclusion/exclusion restrictions for collecting
 * access log data based on request paths, user roles and cache status.
 */
function better_statistics_better_statistics_prelog() {
  // Skip if page is served from cache and Better Statistics is set to
  // exclude logging cached requests.
  $cache_status = better_statistics_served_from_cache();
  if ($cache_status && !variable_get('statistics_access_log_restrictions_cache', TRUE)) {
    better_statistics_request_is_loggable(FALSE);
    return;
  }

  // If there are page-based restrictions, check the page.
  $restrict_pages = variable_get('statistics_access_log_restrictions_page', 0);
  $pages = drupal_strtolower(variable_get('statistics_access_log_restrictions_pages', ''));
  if ($restrict_pages || !empty($pages)) {
    // Make sure drupal_match_path() is available.
    require_once DRUPAL_ROOT . '/' . variable_get('path_inc', 'includes/path.inc');

    // Make sure language is initialized for drupal_get_path_alias().
    global $language_url;
    if (!isset($language_url)) {
      drupal_language_initialize();
    }

    // Convert the Drupal path to lowercase.
    $path = drupal_strtolower(drupal_get_path_alias($_GET['q']));
    // Compare the lowercase internal and lowercase path alias (if any).
    $page_match = drupal_match_path($path, $pages);
    if ($path != $_GET['q']) {
      $page_match = $page_match || drupal_match_path($_GET['q'], $pages);
    }

    if ($page_match xor $restrict_pages) {
      better_statistics_request_is_loggable(FALSE);
      return;
    }
  }

  // If role restrictions are specified, check the array.
  $roles = variable_get('statistics_access_log_restrictions_roles', array());
  $restrictions_count = array_count_values($roles);
  if (isset($restrictions_count[0]) && $restrictions_count[0] < count($roles)) {
    // Skip if user is not part of an included role.
    global $user;
    $roles_check = array_intersect($roles, array_keys($user->roles));
    if (empty($roles_check)) {
      better_statistics_request_is_loggable(FALSE);
      return;
    }
  }

  // If DNT restrictions are specified, check headers.
  if (variable_get('statistics_access_log_restrictions_dnt', FALSE)) {
    // Respect the "do not track" header.
    if (isset($_SERVER['HTTP_DNT']) && $_SERVER['HTTP_DNT']) {
      better_statistics_request_is_loggable(FALSE);
    }
  }
}


/**
 * Implements hook_better_statistics_log().
 *
 * Logs Statistics data in the {accesslog} table.
 */
function better_statistics_better_statistics_log($data) {
  // Check that we're meant to log Statistics to the DB.
  if (variable_get('statistics_log_to_db', TRUE)) {
    // Now that we have data, try to insert it.
    try {
      db_insert('accesslog')->fields($data)->execute();
    }
    catch (Exception $e) {
      // At least log core fields.
      $defaults = better_statistics_get_default_fields();
      $core_fields = array_intersect_key($data, $defaults);
      db_insert('accesslog')->fields($core_fields)->execute();

      // Log the error.
      watchdog('better statistics', 'There was an error collecting statistics data:<br /><br />@error', array('@error' => $e->getMessage()), WATCHDOG_ERROR);
    }
  }
}
