<?php if(!empty($result)) { ?>
<div class="row-fluid performers-masonry">
    <?php 
    foreach($result as $entity_id => $entity) { ?>
    <?php $node = node_load($entity->getBundle());
    $uri = dannyscomedyclub_uri($node);
    print theme('performer_view', array(
        'class' => 'span2 align-center',
        'performer_title' => $node->title,
        'performer_path' => url($uri['path'], array('base_path' => TRUE)),
        'performer_image' => field_view_field('node', $node, 'field_image', 'scaled_down')
    )); ?>
    <?php } ?>
</div>
<?php } ?>