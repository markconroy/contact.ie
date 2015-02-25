<?php
// $Id$

/**
 * @file
 * Provide views data and handlers for views_horizontal_slider.module *  
 */

/*
 * Implementation of hook_views_plugins()
 * IMPORTANT, theme is the name of the tpl with - replaced by _
 * views-horizontal-slider-view.tpl.php -> views_horizontal_slider_view
 */
function views_horizontal_slider_views_plugins() {
  return array(

    'module' => 'views_horizontal_slider',
    'style' => array (
        'views_horizontal_slider' => array(
          'title' => t('Horizontal Slider'),
          'help' => t('Displays Content with a Horizontal Slider Effect.'),
          'handler' => 'views_horizontal_slider_style_plugin', // views_horizontal_slider_style_plugin points to views_horizontal_slider_style_plugin.inc
          'uses row plugin' => TRUE,
          'uses options' => TRUE,
          'uses grouping' => FALSE,
          'type' => 'normal',
          'path' => drupal_get_path('module', 'views_horizontal_slider'),
          'theme path' => drupal_get_path('module', 'views_horizontal_slider'),
          'theme' => 'views_horizontal_slider_view',
        ),
    ),
  );
}

