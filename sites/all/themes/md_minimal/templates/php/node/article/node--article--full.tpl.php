<div class="row-fluid">
    <?php if(!empty($content['field_image_multiple'])) { ?>
    <div class="span4 image_wrapper">
        <?php print drupal_render($content['field_image_multiple']); ?>
    </div>
    <?php } ?>
    <div class="<?php empty($content['field_image_multiple']) ? 'clearfix' : 'span8' ?>">
        <?php print drupal_render($content['body']); ?>
    </div>
</div>