<?php

/**
 * Implements hook_node_info().
 */
function performer_node_info() {
    return array(
        'artistes' => array(
            'name' => t('Artistes'),
            'base' => 'artistes_content',
            'description' => t('Artistes Node Type recording the details of Artistes appeared or appearing'),
            'title_label' => t('Name'),
            'has_title' => 1
        )
    );
}

?>