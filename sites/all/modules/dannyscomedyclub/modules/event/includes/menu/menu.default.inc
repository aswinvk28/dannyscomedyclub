<?php

function event_menu() {
    $items = array();
    
    $items['shows'] = array(
        'title' => 'Shows',
        'page callback' => 'dannyscomedyclub_display_page',
        'page arguments' => array(0),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'menu_name' => 'main-menu',
        'type' => MENU_NORMAL_ITEM,
        'weight' => -10
    );
    
    $items['shows/%dcc_node_url'] = array(
        'title' => 'Shows: ',
        'title arguments' => array(0, 1),
        'title callback' => 'dannyscomedyclub_nodetitle',
        'page callback' => 'dannyscomedyclub_nodetype_view',
        'page arguments' => array(0, 1),
        'load arguments' => array(1),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'type' => MENU_DEFAULT_LOCAL_TASK,
        'delivery callback' => 'dannyscomedyclub_delivery_html'
    );
    
    $items['performances/%dcc_node_url'] = array(
        'title' => 'Performances: ',
        'title arguments' => array(0, 1),
        'title callback' => 'dannyscomedyclub_nodetitle',
        'page callback' => 'dannyscomedyclub_nodetype_view',
        'page arguments' => array(0, 1),
        'load arguments' => array(1),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'type' => MENU_DEFAULT_LOCAL_TASK,
        'delivery callback' => 'dannyscomedyclub_delivery_html'
    );
    
    return $items;
}

?>