<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
if($element['#view_mode'] == 'scaled_down') {
    $info = image_get_info($element['#items'][0]['uri']);
    $position = strrpos($element['#items'][0]['uri'], '.'.$info['extension']);
    $source = substr_replace($element['#items'][0]['uri'], '_w150', $position, 0);
    if(!file_exists(DRUPAL_ROOT . base_path() . 'sites/default/files/' . str_replace('public://', '', $source))) {
        $image = image_load($element['#items'][0]['uri']);
        image_scale($image, '150');
        $position = strrpos($image->source, '.'.$image->info['extension']);
        $source = substr_replace($image->source, '_w150', $position, 0);
        $image->source = $source;
        image_save($image);
    } ?>
<meta itemprop="image" content="<?php print file_create_url($element['#items'][0]['uri']); ?>" />
<div class="<?php echo $classes; ?>" <?php print drupal_attributes($item_attributes_array[0]); ?>>
    <img src="<?php print file_create_url($source); ?>" alt="<?php print $element['#items'][0]['alt']; ?>" 
         title="<?php print $element['#items'][0]['title']; ?>" />
</div>
<?php } else {
?>
<meta itemprop="image" content="<?php print file_create_url($element['#items'][0]['uri']); ?>" />
<div class="<?php echo $classes; ?>" <?php print drupal_attributes($item_attributes_array[0]); ?>>
    <img src="<?php print file_create_url($element['#items'][0]['uri']); ?>" alt="<?php print $element['#items'][0]['alt']; ?>" 
         title="<?php print $element['#items'][0]['title']; ?>" />
</div>

<?php } ?>