<?php

function performance_performance__performance__front_page(&$vars) {
    $performance_entity = $vars['elements']['#entity'];
    $performer_node = $performance_entity->getPerformerEntity()->getBundleNode();
    $peformer_node_view = new PerformerNodeView($performer_node);

    $uri = dannyscomedyclub_uri($performer_node);
    $vars['performer']['path'] = url($uri['path'], array('base_url' => TRUE));
    $vars['description'] = $peformer_node_view->getSummary();
    if(empty($vars['description'])) {
        $performance_node_entity = new PerformanceNodeView($performance_entity->getBundleNode());
        $vars['description'] = $performance_node_entity->getSummary();
    }
    $vars['performer']['title'] = entity_label('performer', $performance_entity->getPerformerEntity());

    $tags = field_get_items('node', $performer_node, 'field_performer_tags');
    $print_tags = array();
    if (!empty($tags)):
        foreach ($tags as $tag) {
            $print_tags['tag_' . $tag['tid']] = array(
                '#type' => 'html_tag',
                '#value' => taxonomy_term_title(taxonomy_term_load($tag['tid'])),
                '#tag' => 'div',
                '#attributes' => array(
                    'class' => 'clearfix'
                )
            );
            if(count($print_tags) == 3) break;
        }
    endif;
    $vars['performer_tags'] = drupal_render($print_tags);

    if(module_exists('performance_type')) {
        $hook = str_replace('event_', '', __FUNCTION__);
        if(module_hook('performance_type', $hook)) {
            module_invoke('performance_type', $hook);
        }
    }

    $performer_press_quotes = entity_get_controller('pressquotation')->readMultipleEntities(array(), array(
        'entity_node_reference_id' => $performer_node->nid
    ),array(
        'quote.range' => 3
    ));
    $performance_press_quotes = entity_get_controller('pressquotation')->readMultipleEntities(array(), array(
        'entity_node_reference_id' => $performance_entity->getBundle()
    ),array(
        'quote.range' => 3
    ));

    $vars['performer_press_quotes'] = !empty($performer_press_quotes) ? entity_view('pressquotation', $performer_press_quotes, 'general_view') : '';
    $vars['performance_press_quotes'] = !empty($performance_press_quotes) ? entity_view('pressquotation', $performance_press_quotes, 'general_view') : '';

    $vars['performer_image'] = field_view_field('node', $performer_node, 'field_image', 'scaled_down');

    $types = require DRUPAL_ROOT.base_path().drupal_get_path('module', 'dannyscomedyclub') . '/config/performances_types.inc';
    $taxonomy_entity = new TaxonomyEntity(array(
        'tid' => $performance_entity->getPerformanceType()
    ), 'taxonomy_term');
    $vars['itemType'] = $types[$taxonomy_entity->getName()];
    $vars['classes_array'][] = $performance_entity->isNew() == 1 ? 'performer_act_first' : '';
}

function performance_performance__performance__video_view(&$vars) {
    $entity = $vars['elements']['#entity'];
    $vars['video_id'] = $entity->getYtVideoId();
    $file = file_load($entity->getParentEntity()->getEventImage());
    if(!empty($file)) {
        $vars['image_url'] = $file->uri;
    }
}

function show_show__show__front_page(&$vars) {
    $entity = $vars['elements']['#entity'];
    $performances = $entity->getPublishedPerformances();
    $performances = entity_get_controller('performance')->setNewActs($performances);
    $entity_view = entity_view('performance', $performances, 'front_page');
    $vars['published_performances'] = drupal_render($entity_view);
    $show_entity_view = new ShowEntityView($entity);
    if(module_exists('venue')) {
        $vars['venue'] = array();
        $vars['venue']['title'] = entity_label('venue', $entity->getVenueEntity());
        $venue_uri = entity_uri('venue', $entity->getVenueEntity());
        $vars['venue']['path'] = url($venue_uri['path'], array('base_url' => TRUE));
    }
}
    
?>
