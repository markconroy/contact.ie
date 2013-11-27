<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */


/**
 * @defgroup better_statistics Better Statistics module integrations.
 *
 * Module integrations with the Better Statistics module.
 */

/**
 * @defgroup better_statistics_hooks Better Statistics' hooks
 * @{
 * Hooks that can be implemented by other modules in order to extend the Better
 * Statistics module.
 */

/**
 * Register Statistics API information. This is required for your module to have
 * its include files loaded.
 *
 * @return
 *   An array with the following possible keys:
 *   - api: (required) The version of the Statistics API the module implements.
 *     The current version of the API is 1.0.
 *   - path: (optional) If the include is stored somewhere other than within the
 *     root module directory, specify its path here.
 *   - file: (optional) If the include's file name is anything other than
 *     MODULE.statistics.inc, specify it here.
 */
function hook_statistics_api() {
  // In this example, Better Statistics hooks and callbacks would be located
  // somewhere like: /sites/all/modules/example/statistics/stats_fields.inc
  return array(
    'version' => 1,
    'path' => drupal_get_path('module', 'example') . '/statistics',
    'file' => 'stats_fields.inc',
  );
}

/**
 * Declare additional fields for possible inclusion in {accesslog}.
 *
 * This hook allows your module to expose fields for inclusion in the accesslog.
 * By default, your field will not be enabled, but a user can enable it for data
 * collection by checking its box on the Statistics configuration page.
 *
 * Once checked, Better Statistics adds your field's schema to the {accesslog}
 * with a call to db_add_field() using your declared schema. It will immediately
 * begin collecting data using the callback you define here.
 *
 * When a user unchecks your field, db_drop_field() is called and all data for
 * the field is wiped with it.
 *
 * If and when you make updates in this hook, Better Statistics will register
 * your changes on cache flushes and cron runs. Be extremely cautious when
 * modifying your field's schema; avoid it if at all possible. If detected, the
 * module will perform db_change_field() using your modified schema.
 *
 * Be careful in your use of the t() function on user-facing strings. See the
 * provided examples below.
 *
 * This hook and your field callbacks should be placed in an include of the form
 * MODULE.statistics.inc.
 *
 * @return
 *   An array of information about the fields for which your module can provide
 *   data (keyed by the field name to use in the database) to be inserted into
 *   the Access Log at the end of each page request. Each field must declare at
 *   least a schema and a callback function, but can also provide more detailed
 *   information regarding Views integration. Attributes for each field are:
 *   - schema: An array representing the schema data structure used by Drupal's
 *     schema API to create your field. Modifications to this should be rare;
 *     schema changes will be registered and executed on cron and cache flushes.
 *   - callback: A function that returns data for the field. This function must
 *     take a single argument (the field name you provide), and must return data
 *     properly typed and within range for your field's declared schema. Failure
 *     to do so will result in complete data loss for the row. Also note that if
 *     you can guarantee a PHP 5.3+ running environment, this can be a closure.
 *   - views_field: (optional) An array of Views handlers suitable for use in a
 *     call to hook_views_data() or hook_views_data_alter(). If no information
 *     is provided, Better Statistics will try and make its best guess on how to
 *     expose your field to Views. Note you can set this to FALSE to disable
 *     Views integration for your field.
 *
 * @see hook_statistics_api()
 * @see _better_statistics_get_custom_fields_by_module()
 * @see schemaapi
 * @see hook_views_data()
 */
function hook_better_statistics_fields() {
  $fields = array();

  // This array key will be used like: {accesslog}.my_module_foo, so take care
  // not to collide with fields provided by other modules, but also be mindful
  // of the limits of database field name lengths. Additionally, if you don't
  // provide Views information, it will be used as the title of the field.
  $fields['my_module_foo'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      // If you don't provide any additional Views information, this will be
      // used when presenting admins with your field.
      'description' => 'A description about foo.',
    ),
    // This will be called like: my_module_get_values('my_module_foo');
    'callback' => 'my_module_get_values',
  );

  // Another basic example with a few more options.
  $fields['my_module_bar'] = array(
    'schema' => array(
      'type' => 'int',
      'size' => 'normal',
      // If 'not null' is set to TRUE, you must define a default value.
      'not null' => TRUE,
      'default' => 0,
      'description' => 'A description about bar.',
    ),
    // Note that this callback function runs on both regular page requests and
    // cached page requests. During the latter, Drupal's bootstrap phase is
    // low and many functions you're used to having will not be available. In
    // all likelihood, the module for which you are implementing the Statistics
    // API may not even be loaded. You are responsible for ensuring any inc or
    // module dependencies are loaded when your callback runs. You may find the
    // following function of some use:
    // @see better_statistics_served_from_cache()
    'callback' => 'my_module_get_values',
    'views_field' => array(
      // This is user facing and should be passed through t(), but here, it must
      // return in English, or else it may become cached in the wrong language.
      // The string will be passed properly through t() when actually presented.
      'title' => t('Bar', array(), array('langcode' => 'en')),
      'help' => t('A description about bar for site builders.', array(), array('langcode' => 'en')),
      // Default Views handlers will be guessed based on the schema type.
    ),
  );

  // A more advanced example.
  $fields['my_module_baz'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      'description' => 'A description about baz.',
    ),
    // If you can assume a PHP 5.3 envrionment, you can use a closure:
    'callback' => function($field) {
      $baz = '';
      // Your code here...
      return truncate_utf8($baz, 255);
    },
    'views_field' => array(
      'title' => t('Baz', array(), array('langcode' => 'en')),
      'help' => t('A description about baz for site builders.', array(), array('langcode' => 'en')),
      // Provide specialized Views handlers for your field. Note that you are
      // responsible for ensuring these classes are loaded properly.
      'field' => array(
        'handler' => 'my_special_views_field_handler',
      ),
      'sort' => array(
        'handler' => 'my_special_sort_handler',
      ),
      'filter' => array(
        'handler' => 'my_special_filter_handler',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'my_special_argument_handler',
      ),
    ),
  );

  return $fields;
}

/**
 * Allows modules to react just before Better Statistics performs access log
 * field data collection and just after all module.statistics.inc files have
 * been loaded.
 *
 * A good use of this is to call better_statistics_request_is_loggable().
 *
 * Implementations of this hook should be placed in your module.statistics.inc.
 */
function hook_better_statistics_prelog() {
  // Never record statistics for user 1.
  global $user;
  if ($user->uid == 1) {
    better_statistics_request_is_loggable(FALSE);
  }
}

/**
 * Log access statistics.
 *
 * This hook allows modules to route access statistics to custom destinations in
 * custom formats such as syslog, flat files, csv, etc.
 *
 * Note that Better Statistics logs access data to the Drupal {accesslog} table
 * by default. You may wish to disable this functionality by instructing users
 * to add a variable setting in settings.php, or manually doing so yourself by
 * setting the global variable in hook_better_statistics_prelog().
 *
 * The variable in question is "statistics_log_to_db."
 *
 * @param $data
 *   An array of access statistics data keyed by field name.
 */
function hook_better_statistics_log($data) {
  // Send data to Google Analytics using php-ga.
  $tracker = new GoogleAnalytics\Tracker('UA-12345678-9', 'example.com');
  $session = new GoogleAnalytics\Session();
  $visitor = new GoogleAnalytics\Visitor();
  $visitor->setIpAddress(ip_address());
  $page = new GoogleAnalytics\Page(request_path());
  $n = 1;
  foreach ($data as $name => $value) {
    $custom_var = new GoogleAnalytics\CustomVariable($n++, $name, $value);
    $tracker->addCustomVar($custom_var);
  }
  $tracker->trackPageview($page, $session, $visitor);
}

/**
 * @}
 */
