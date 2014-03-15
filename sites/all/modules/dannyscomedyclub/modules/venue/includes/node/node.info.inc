<?php

/**
 * Implements hook_node_info().
 */
function venue_node_info() {
    return array(
        'venue' => array(
            'name' => t('Venue'),
            'base' => 'venue_content',
            'description' => t('Venue Node Type recoding each Show'),
            'title_label' => t('Name'),
            'has_title' => 1
        )
    );
}

?>