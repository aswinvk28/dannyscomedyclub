<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<div class="<?php echo $classes; ?>" <?php print drupal_attributes($item_attributes_array[0]); ?>>
    <img src="<?php print file_create_url($element['#items'][0]['uri']); ?>" alt="<?php print $element['#items'][0]['alt']; ?>" 
         title="<?php print $element['#items'][0]['title']; ?>" />
</div>