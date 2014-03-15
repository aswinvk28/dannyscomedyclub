<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if($view_mode == 'tabs_content_front') { ?>
    
    <div id="<?php echo drupal_html_class($title); ?>" class="js-pane tab-pane">
        <div class="row-fluid js-pane-content">
            <div class="span5 image_wrapper">
                <?php print drupal_render($content['field_image_multiple']); ?>
            </div>
            <div class="span7 flarge spaced_description">
                <div class="column_title">
                    <h2 <?php print $title_attributes; ?>><?php echo $title; ?></h2>
                </div>
                <?php print drupal_render($content['body']); ?>
            </div>
        </div>
    </div>

<?php } elseif($view_mode == 'tabs_icon_front') { ?>

    <li>
        <a class="js_tabs_button" href="#<?php print drupal_html_class($title); ?>">
            <?php print drupal_render($content['field_image']); ?>
        </a>
    </li>
    
<?php } else { ?>

    <div class="row-fluid">
        <div class="span4 image_wrapper">
            <?php print drupal_render($content['field_image_multiple']); ?>
        </div>
        <div class="span8">
            <?php print drupal_render($content['body']); ?>
        </div>
    </div>
    
<?php } ?>

