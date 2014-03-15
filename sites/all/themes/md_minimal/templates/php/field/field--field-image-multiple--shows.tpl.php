
<?php foreach($items as $delta => $item) { ?>

<div class="<?php echo $classes; ?>">
    
    <h4 class="decolumn_mini white">
        <span><?php echo $item['#item']['title'] ? $item['#item']['title'] : node_page_title($element['#object']); ?></span>
    </h4>
    
    <?php $image = image_load($item['#item']['uri']);
    image_scale($image, '320');
    $position = strrpos($image->source, '.'.$image->info['extension']);
    $source = substr_replace($image->source, '_w320', $position, 0);
    $image->source = $source;
    if(!file_exists(DRUPAL_ROOT . base_path() . 'sites/default/files/' . str_replace('public://', '', $image->source))) {
        image_save($image);
    }
    
    ?>
    
    <a class="colorbox-image" href="<?php print file_create_url($item['#item']['uri']); ?>" <?php print drupal_attributes($item_attributes_array[$delta]); ?>>
    <img src="<?php print file_create_url($image->source); ?>" alt="<?php print $item['#item']['alt']; ?>"
         title="<?php print $item['#item']['title']; ?>" />
    </a>
    
    <p><?php echo $image_caption; ?></p>
    
</div>

<?php } ?>