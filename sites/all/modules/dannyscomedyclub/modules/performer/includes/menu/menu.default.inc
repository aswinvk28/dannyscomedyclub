<?php

function performer_menu() {
    $items = array();
    
    $items['artistes'] = array(
        'title' => 'Artistes',
        'page callback' => 'dannyscomedyclub_display_content',
        'page arguments' => array(0),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'menu_name' => 'main-menu',
        'type' => MENU_NORMAL_ITEM,
        'weight' => -10
    );
    
    $items['artistes/page/%'] = array(
        'title' => 'Artistes',
        'page callback' => 'dannyscomedyclub_display_content',
        'page arguments' => array(0, 1, 2),
        'load arguments' => array(0, 1, 2),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'type' => MENU_FOUND,
    );
    
    $items['performer/page/%'] = array(
        'page callback' => 'artistes_page_list',
        'page arguments' => array(2),
        'load arguments' => array(0, 1, 2),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'type' => MENU_FOUND,
        'delivery callback' => 'ajax_deliver'
    );
    
    $items['artistes/%dcc_node_url'] = array(
        'title' => 'Artistes: ',
        'title arguments' => array(0, 1),
        'title callback' => 'dannyscomedyclub_nodetitle',
        'page callback' => 'dannyscomedyclub_nodetype_view',
        'page arguments' => array(0, 1),
        'load arguments' => array(1),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'type' => MENU_FOUND,
        'delivery callback' => 'dannyscomedyclub_delivery_html'
    );
    
    return $items;
}

?>