<?php

if( !empty($result) ): ?>

<div class="column clearfix" itemprop="mainContentOfPage" itemscope itemtype="http://schema.org/WebPageElement">

<?php $list_item = ''; $tab_item = '';
while( $view = array_shift($result) ) :
    
    $content_view = $view;
    $view['#view_mode'] = 'tabs_icon_front';
    $list_item .= drupal_render($view);
    
    $content_view['#view_mode'] = 'tabs_content_front';
    $tab_item .= drupal_render($content_view);

endwhile;
?>

    <div id="js_fade" class="clearfix prelative">
        <div class="js-pane-holder row-fluid pull-left border_radius_large">
            <ul class="unstyled js_tabs nav nav-tabs">
                <?php echo $list_item; ?>
            </ul>
            <?php echo $tab_item; ?>
        </div>
    </div>

</div>

<?php endif; ?>