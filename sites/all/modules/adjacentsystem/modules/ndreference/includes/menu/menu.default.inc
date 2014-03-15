<?php

function ndreference_menu() {
    $items = array();
    
    $items['review/%ndreference_entity_object'] = array(
        'title' => 'Reviews: ',
        'title callback' => 'dannyscomedyclub_entitytitle',
        'title arguments' => array(1),
        'page callback' => 'dannyscomedyclub_entityview',
        'page arguments' => array(1, 'full'),
        'load arguments' => array('review'),
        'file' => 'entityfunctionality.pages.inc',
        'file path' => drupal_get_path('module', 'entityfunctionality'),
        'access arguments' => array('access content'),
        'type' => MENU_DEFAULT_LOCAL_TASK
    );
    
    $items['pressrelease/%ndreference_entity_object'] = array(
        'title' => 'Press Releases: ',
        'title callback' => 'dannyscomedyclub_entitytitle',
        'title arguments' => array(1),
        'page callback' => 'dannyscomedyclub_entityview',
        'page arguments' => array(1, 'full'),
        'load arguments' => array('press_release'),
        'file' => 'entityfunctionality.pages.inc',
        'file path' => drupal_get_path('module', 'entityfunctionality'),
        'access arguments' => array('access content'),
        'type' => MENU_DEFAULT_LOCAL_TASK
    );
    
    return $items;
}

?>