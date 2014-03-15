<?php

function venue_menu() {
    $items = array();
    
    $items['venue/%venue_entity_object'] = array(
        'title' => 'Venue: ',
        'title callback' => 'dannyscomedyclub_entitytitle',
        'title arguments' => array(1),
        'page callback' => 'dannyscomedyclub_entityview',
        'page arguments' => array(1, 'full'),
        'load arguments' => array(1),
        'file' => 'entityfunctionality.pages.inc',
        'file path' => drupal_get_path('module', 'entityfunctionality'),
        'access arguments' => array('access content'),
        'type' => MENU_DEFAULT_LOCAL_TASK
    );
    
    $items['venue'] = array(
        'title' => 'Venues',
        'page callback' => 'dannyscomedyclub_display_page',
        'page arguments' => array(0),
        'file' => 'dannyscomedyclub.pages.inc',
        'file path' => drupal_get_path('module', 'dannyscomedyclub'),
        'access arguments' => array('access content'),
        'menu_name' => 'main-menu',
        'type' => MENU_NORMAL_ITEM,
        'weight' => -8
    );
    
    return $items;
}

?>