<div id="<?php echo drupal_html_class($title); ?>" class="js-pane tab-pane">
    <div class="clearfix js-pane-content">
        <div class="clearfix image_wrapper">
            <?php print drupal_render($content['field_image_multiple']); ?>
        </div>
        <div class="clearfix spaced_description">
            <div class="column_title">
                <h2 <?php print $title_attributes; ?>><?php echo $title; ?></h2>
            </div>
            <?php print drupal_render($content['body']); ?>
        </div>
    </div>
</div>