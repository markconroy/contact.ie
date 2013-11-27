<?php

/**
 * @file
 * Views hooks for the Better Statistics module.
 */


/**
 * Implements hook_views_data_alter().
 *
 * Exposes selected fields in the accesslog to Views.
 */
function better_statistics_views_data_alter(&$data) {
  // Fetch active statistics fields.
  $current = variable_get('better_statistics_fields', better_statistics_get_default_fields());

  // For each field, if appropriate, expose the field to Views.
  foreach ($current as $field => $field_data) {
    if ($field_data['views_field']) {
      // Properly translate the title.
      if (isset($field_data['views_field']['title'])) {
        $field_data['views_field']['title'] = t($field_data['views_field']['title']);
      }

      // Properly translate the help/description.
      if (isset($field_data['views_field']['help'])) {
        $field_data['views_field']['help'] = t($field_data['views_field']['help']);
      }

      // Properly translate any labels.
      foreach ($field_data['views_field'] as &$handler) {
        if (is_array($handler) && isset($handler['label'])) {
          $handler['label'] = t($handler['label']);
        }
      }

      // Make views aware of the field in the accesslog.
      $data['accesslog'][$field] = $field_data['views_field'];
    }
  }
}
