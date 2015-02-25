<?php

/**
 * @file
 * Drush integration of Better Statistics.
 */


/**
 * Implements hook_drush_command().
 */
function better_statistics_drush_command() {
  $items = array();

  $items['stats-ls'] = array(
    'description' => 'List statistics fields.',
    'drupal dependencies' => array('better_statistics'),
    'options' => array(
      'all' => 'Show all fields. If no flags are provided, this is the default.',
      'enabled' => 'Show only active fields.',
      'disabled' => 'Show only fields not currently enabled.',
      'pipe' => 'Output each field name, one per line.',
    ),
    'examples' => array(
      'drush stats-ls' => 'Returns a list of all statistics fields.',
      'drush stats-ls --enabled' => 'Returns a list of enabled/active statistics fields.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );
  $items['stats-en'] = array(
    'description' => 'Enable the specified statistics field(s).',
    'drupal dependencies' => array('better_statistics'),
    'arguments' => array(
      'fields' => 'One or several statistics fields to enable. Use ‘drush stats-ls‘ for a full list.',
    ),
    'examples' => array(
      'drush stats-en peak_memory' => 'Enable the peak_memory field.',
      'drush stats-en cache peak_memory' => 'Enable the cache and peak_memory fields.',
    ),
  );
  $items['stats-dis'] = array(
    'description' => 'Disable the specified statistics field(s). Note that this will permanently delete all data for the specified field(s).',
       'drupal dependencies' => array('better_statistics'),
    'arguments' => array(
      'fields' => 'One or several statistics fields to disable. Use ‘drush stats-ls‘ for a full list.',
    ),
    'examples' => array(
      'drush stats-dis peak_memory' => 'Disable the peak_memory field.',
      'drush stats-dis cache peak_memory' => 'Disable the cache and peak_memory fields.',
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function better_statistics_drush_help($section) {
  switch ($section) {
    case 'drush:statistics-list-fields':
      return dt('Returns a list of Statistics API fields. Defaults to all fields, specify flags for only those enabled or only those disabled.');
    case 'drush:statistics-enable-fields':
      return dt('Enables one or several statistics fields.');
  }
}

/**
 * Drush command callback for stats-ls.
 */
function drush_better_statistics_stats_ls() {
  module_load_include('inc', 'better_statistics', 'better_statistics.admin');
  $available = _better_statistics_get_custom_fields_by_module();
  $active = variable_get('better_statistics_fields', better_statistics_get_default_fields());

  // Options.
  $options['enabled'] = drush_get_option('enabled');
  $options['disabled'] = drush_get_option('disabled');

  // Assemble the list of fields to print.
  foreach ($available as $module => $fields) {
    $module_info = system_get_info('module', $module);
    $fields_by_module[$module_info['name']] = array();
    foreach ($fields as $field => $data) {
      $description = '';
      if (isset($data['views_field']['help'])) {
        $description = dt($data['views_field']['help']);
      }
      elseif (isset($data['schema']['description'])) {
        $description = dt($data['schema']['description']);
      }

      // Print according to the supplied options, if any.
      $enabled = $options['enabled'] && isset($active[$field]);
      $disabled = $options['disabled'] && !isset($active[$field]);
      $neither = !$options['enabled'] && !$options['disabled'];
      if ($enabled || $disabled || $neither) {
        $fields_by_module[$module_info['name']][$field] = $description;
        $fields[$field] = $description;
      }
    }
  }

  // Print either an ini-format list or a formatted ASCII table
  if (drush_get_option('pipe')) {
    drush_print_pipe(array_keys($fields));
  }
  else {
    foreach ($fields_by_module as $module => $mod_fields) {
      if (count($mod_fields) > 0) {
        drush_print($module);
        drush_print_table(drush_key_value_to_array_table($mod_fields));
      }
    }
  }
}

/**
 * Drush command callback for stats-en.
 */
function drush_better_statistics_stats_en($fields) {
  module_load_include('inc', 'better_statistics', 'better_statistics.admin');
  $fields = func_get_args();
  $active = variable_get('better_statistics_fields', better_statistics_get_default_fields());
  $available = _better_statistics_get_custom_fields_by_module();

  foreach ($fields as $index => $field) {
    if (!_better_statistics_field_exists($field)) {
      unset($fields[$index]);
      drush_print(dt("The @field field doesn't exist. Use drush stats-ls to view a full list of available fields.", array('@field' => $field)));
    }
    elseif (isset($active[$field])) {
         unset($fields[$index]);
      drush_print(dt('The @field field is already enabled.', array('@field' => $field)));
    }
  }

  if (empty($fields)) {
    return drush_log(dt('There were no fields that could be enabled.'), 'ok');
  }
  else {
    // Inform the user which fields will be enabled.
    drush_print(dt('The following statistics fields will be enabled: !fields', array('!fields' => implode(', ', $fields))));
    if(!drush_confirm(dt('Do you really want to continue?'))) {
      return drush_user_abort();
    }

    // Enable the fields here.
    $enabled = better_statistics_enable_fields($fields);

    // Print confirmation of field enablement.
    drush_print(dt("The following fields were successfully enabled: @fields", array('@fields' => implode(', ', $enabled))));
  }
}

/**
 * Drush command callback for stats-dis.
 */
function drush_better_statistics_stats_dis($fields) {
  module_load_include('inc', 'better_statistics', 'better_statistics.admin');
  $fields = func_get_args();
  $active = variable_get('better_statistics_fields', better_statistics_get_default_fields());
  $available = _better_statistics_get_custom_fields_by_module();

  foreach ($fields as $index => $field) {
    if(!_better_statistics_field_exists($field)) {
      unset($fields[$index]);
      drush_print(dt("The @field field doesn't exist. Use drush stats-ls to view a full list of available fields.", array('@field' => $field)));
    }
    elseif (!isset($active[$field])) {
      unset($fields[$index]);
      drush_print(dt("The @field field isn't enabled.", array('@field' => $field)));
    }
  }

  if (empty($fields)) {
    return drush_log(dt('There were no fields that could be disabled.'), 'ok');
  }
  else {
    // Inform the user which fields will be disabled.
    drush_print(dt('The following statistics fields will be disabled: !fields. All data collected for the specified field(s) will be permanently deleted.', array('!fields' => implode(', ', $fields))));
    if(!drush_confirm(dt('Do you really want to continue?'))) {
      return drush_user_abort();
    }

    // Disable the fields here.
    $disabled = better_statistics_disable_fields($fields);

    // Print confirmation of field disablement.
    drush_print(dt("The following fields were successfully disabled: @fields", array('@fields' => implode(', ', $disabled))));
  }
}


/**
 * Helper function to determine whether a field is even declared by a module.
 *
 * @param $field
 *   The name of the field to be checked.
 *
 * @return
 *   TRUE if the field exists, FALSE otherwise.
 */
function _better_statistics_field_exists($field) {
  static $declared_fields = array();

  // Load all fields by module.
  if (empty($declared_fields)) {
    module_load_include('inc', 'better_statistics', 'better_statistics.admin');
    $declared_fields = _better_statistics_get_custom_fields_by_module();
  }

  foreach ($declared_fields as $module => $fields) {
    if (array_key_exists($field, $fields)) {
      return TRUE;
    }
  }

  return FALSE;
}
