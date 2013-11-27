<?php

/**
 * @file
 * Views settings, output and data validation
  
 */


class views_horizontal_slider_style_plugin extends views_plugin_style {
  
  //default options
  function option_definition() {
    $options = parent::option_definition();

    $options['animate_in']  =  array('default' => 400);
    $options['animate_out'] =  array('default' => 400);
    $options['min_width']   = array('default' => 100);
    $options['max_width']   =  array('default' => 300);
    $options['activated_item']   =  array('default' => 2);

    $options['caption_field_name']   =  array('default' => '');
    $options['caption_field_fadein']   =  array('default' => 500);
    $options['caption_field_fadeout']   =  array('default' => 500);
    
    return $options;
  }

function options_form(&$form, &$form_state) {
  parent::options_form($form, $form_state);

  unset($form['grouping']);
  //unset($form['type']);

  $form['animate_in'] = array(
    '#type' => 'textfield',
    '#title' => t('Animate In'),
    '#required' => TRUE,
    '#description' => t('Specify the Animation In Speed'),
    '#default_value' => $this->options['animate_in'],
    );

  $form['animate_out'] = array(
    '#type' => 'textfield',
    '#title' => t('Animate Out'),
    '#required' => TRUE,
    '#description' => t('Specify the Animation Out Speed'),
    '#default_value' => $this->options['animate_out'],
    );

  $form['min_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Min Width'),
    '#required' => TRUE,
    '#description' => t('Minimum width of an image/item'),
    '#default_value' => $this->options['min_width'],
    );
  
  $form['max_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Width'),
    '#required' => TRUE,
    '#description' => t('Maximum width of an image/item'),
    '#default_value' => $this->options['max_width'],
    );

   $form['activated_item'] = array(
    '#type' => 'textfield',
    '#title' => t('Active Item'),
    '#required' => FALSE,
    '#description' => t('The item that is active on page load. Start: 1 to the number of images/items you have. '),
    '#default_value' => $this->options['activated_item'],
    );

   $form['caption_field_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption field name'),
    '#required' => FALSE,
    '#description' => t('Name of the field that will be used as caption. You only need that if you want to fade in a caption on hover. You can get the field name out of the html code (for "example views-field-title"). Leave empty if not used.'),
    '#default_value' => $this->options['caption_field_name'],
    );

   $form['caption_field_fadein'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption field Fade in speed'),
    '#required' => FALSE,
    '#description' => t('Fade in speed '),
    '#default_value' => $this->options['caption_field_fadein'],
    );

   $form['caption_field_fadeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption field Fade out speed'),
    '#required' => FALSE,
    '#description' => t('Fade out speed '),
    '#default_value' => $this->options['caption_field_fadeout'],
    );

  }

//Validating the inputs
//@TODO validation
//seems to be a bug?

function options_validate($form, &$form_state) {

  parent::options_validate($form, $form_state);
  $options = &$form_state['values']['style_options'];

  if (!is_numeric($options['max_width'])) {
    form_error($form['max_width'], t('Please specify a numerical value for Max Width'));
  }
  if (!is_numeric($options['min_width'])) {
      form_error($form['min_width'], t('Please specify a numerical value for Min Width'));
  }
  if (!is_numeric($options['animate_in'])) {
      form_error($form['animate_in'], t('Please specify a numerical value for Animate In'));
  }
  if (!is_numeric($options['animate_out'])) {
    form_error($form['animate_out'], t('Please specify a numerical value for Animate Out'));
  }
  if (!is_numeric($options['activated_item'])) {
    form_error($form['activated_item'], t('Please specify a numerical value for Activated Item'));
  }
   if (!is_numeric($options['caption_field_fadein'])) {
    form_error($form['activated_item'], t('Please specify a numerical value for fade in'));
  }
   if (!is_numeric($options['caption_field_fadeout'])) {
    form_error($form['activated_item'], t('Please specify a numerical value for fade out'));
  }
}

}







