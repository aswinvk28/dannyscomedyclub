<?php foreach($items as $delta => $item) { ?>

<div class="<?php echo $classes; ?>" <?php print drupal_attributes($item_attributes_array[$delta]); ?>>
    <img src="<?php print file_create_url($element['#items'][$delta]['uri']); ?>" alt="<?php print $element['#items'][$delta]['alt']; ?>" 
         title="<?php print $element['#items'][$delta]['title']; ?>" />
</div>

<?php } ?>