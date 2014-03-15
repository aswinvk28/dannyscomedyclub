<?php 
if(!empty($items)): $output = array(); ?>

<div class="clearfix">
    <?php print $top_content; ?>
    <ul class="<?php !empty($classes) ? $classes : 'act-tags'; ?>">
<?php 
foreach($items as $item) {
    $output[] = '<li class="act-tag pull-left white">'. !empty($item['path']) ? '<a href="'. $item['path'] . '"</a>' : '' . $item['value'] . '</li>';
}

print implode('<li class="pull-left"> | </li>', $output); ?>

    </ul></div>
<?php endif;