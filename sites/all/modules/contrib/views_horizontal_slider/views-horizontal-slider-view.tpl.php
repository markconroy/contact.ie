<?php

/**
 * @file views-view-horizontal-slider.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 * 
 * @TODO Put the first/last logic into module code
 * @TODO put the active classes logik somehow into module code not here
 */
?>
<div class="views_horizontal_slider views_horizontal_slider-<?php print $view->vid; ?> views_horizontal_slider-<?php print $view->vid; ?>">
<?php //dsm($variables);   ?>
<div class="item-list">
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  
    <?php foreach ($rows as $id => $row): ?>
        <?php //dsm($id);   ?>
        <?php //dsm('id:'.(($variables['options']['activated_item'])));   ?>


      <?php if ( ($id == 0) &&  ( $id == (($variables['options']['activated_item'])-1) )): ?>
       <li class="<?php print "hslider-first hslider-active"; ?>"><?php print $row; ?></li>

      <?php elseif ($id == 0): ?>
       <li class="<?php print "hslider-first"; ?>"><?php print $row; ?></li>

     <?php elseif ( $id == (($variables['options']['activated_item'])-1) ): ?>
      <li class="<?php print "hslider-active"; ?>"><?php print $row; ?></li>

      <?php elseif ($id == (count($rows)-1) ): ?>
       <li class="<?php print "hslider-last"; ?>"><?php print $row; ?></li>

      <?php else: ?>
       <li class="<?php print 'hitem-' . $id; ?>"><?php print $row; ?></li>
      <?php endif; ?>
      
    <?php endforeach; ?>    
  
</div>
  
</div>
