<?php

/**
 * Implements hook_node_info().
 */
function event_node_info() {
    return array(
        'performances' => array(
            'name' => t('Performances'),
            'base' => 'performances_content',
            'description' => t('Performances Node Type recording each performance of the show and performer'),
            'title_label' => t('Title'),
            'has_title' => 1
        ),
        'shows' => array(
            'name' => t('Shows'),
            'base' => 'shows_content',
            'description' => t('Shows Node Type recoding each Show'),
            'title_label' => t('Name'),
            'has_title' => 1
        )
    );
}

?>