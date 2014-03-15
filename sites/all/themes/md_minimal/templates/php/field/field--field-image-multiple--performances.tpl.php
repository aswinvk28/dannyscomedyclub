
<?php foreach($items as $delta => $item) { ?>

<div class="<?php echo $classes; ?>">
    
    <?php 
    $info = image_get_info($item['#item']['uri']);
    $position = strrpos($item['#item']['uri'], '.'.$info['extension']);
    $source = substr_replace($item['#item']['uri'], '_w320', $position, 0);
    if(!file_exists(DRUPAL_ROOT . base_path() . 'sites/default/files/' . str_replace('public://', '', $source))) {
        $image = image_load($item['#item']['uri']);
        image_scale($image, '320');
        $position = strrpos($image->source, '.'.$image->info['extension']);
        $source = substr_replace($image->source, '_w320', $position, 0);
        $image->source = $source;
        image_save($image);
    }
    ?>
    
    <?php print $photos_title; ?>
    
    <a class="colorbox-image" href="<?php print file_create_url($item['#item']['uri']); ?>" <?php print drupal_attributes($item_attributes_array[$delta]); ?>>
    <img src="<?php print file_create_url($source); ?>" alt="<?php print $item['#item']['alt']; ?>"
         title="<?php print $item['#item']['title']; ?>" />
    </a>
    <p><?php print $image_caption; ?></p>
    
</div>

<?php } ?>