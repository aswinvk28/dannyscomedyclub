<?php

function performances_content_validate($node) {
    $show_nodes = node_load_multiple(array(), array(
        'type' => 'shows'
    ));
    $performer_entities = entity_load('performer');
    
    if(!array_key_exists($node->entity_performer_id, $performer_entities)) {
        form_set_error('entity_performer_id', t('Check the Performer Selected Value'));
    }
    if(!array_key_exists($node->entity_node_shows_id, $show_nodes)) {
        form_set_error('entity_node_shows_id', t('Check the Show Selected Node Value'));
    }
    
    $term = taxonomy_term_load($node->entity_taxonomy_performances_types_id);
    $vocab = taxonomy_vocabulary_machine_name_load('performances_types');
    if(!empty($term) && ($term->vid !== $vocab->vid)) {
        form_set_error('entity_taxonomy_performances_types_id', 'Select valid Performance Type');
    }
    
    $performance_order = (int) $node->performance_order;
    if(!empty($performance_order) && ( $performance_order < 1 || $performance_order > 255 )) {
        form_set_error('performance_order', 'Enter Valid Number for order');
    }
    
    if(!empty($node->performance_video) && !preg_match('/^http:\/\/\w{0,3}.?youtube+\.\w{2,3}\/watch\?v=[\w-]{11}$/', $node->performance_video)) {
        form_set_error('performance_video', t('Enter valid Performance Video URL like @URL', array('@URL' => "http://www.youtube.com/watch?v='ID'")));
    }
    
    EventCRUD::event_form_validate($node);
}

function performances_content_form($node, &$form_state) {
    $form = array();
    $node = $form_state['node'];
    PerformanceCRUD::performance_node_form($form, $form_state, $node);
    return $form;
}

function performance_form_performances_node_form_alter(&$form, &$form_stte, $form_id) {
    $form['title']['#weight'] = -5;
    $form['title']['#description'] = t('Performance Title');
    $form['title']['#required'] = TRUE;
    
    $form['#submit'][] = 'performance_node_form_submit';
}

?>