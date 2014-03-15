<?php

function venue_content_form($node, &$form_state) {
    $form = array();
    VenueCRUD::venue_node_form($form, $form_state, $node);
    return $form;
}

function venue_content_validate($node) {
    if(!drupal_validate_utf8($node->document_body)) {
        form_set_error('document_body', 'Enter valid strings for Document Body');
    }
    
    if(!drupal_validate_utf8($node->venue_address)) {
        form_set_error('venue_address', t('Enter Valid Venue Address'));
    }
    
    if(!drupal_validate_utf8($node->venue_location)) {
        form_set_error('venue_location', t('Enter Valid Location for the venue'));
    }
    
    if(!empty($node->venue_telephone) && !preg_match('/^[\d\s]{7,}$/', $node->venue_telephone)) {
        form_set_error('venue_telephone', t('Enter Valid Telephone Number'));
    }
    
    if(!empty($node->venue_url) && !preg_match('/\b([\d\w\.\/\+\-\?\:]*)((ht|f)tp(s|)\:\/\/|[\d\d\d|\d\d]\.[\d\d\d|\d\d]\.|www\.|\.tv|\.ac|\.com|\.edu|\.gov|\.int|\.mil|\.net|\.org|\.biz|\.info|\.name|\.pro|\.museum|\.co)([\d\w\.\/\%\+\-\=\&amp;\?\:\\\&quot;\'\,\|\~\;]*)\b/', 
                $node->venue_url)) {
            form_set_error('venue_url', 'Enter valid Venue URL');
    }
    
    if(!empty($node->venue_geo_lat) && !preg_match('/^(-?(90|(\d|[1-8]\d)(\.\d{1,6}){0,1}))$/', $node->venue_geo_lat)) {
        form_set_error('venue_geo_lat', t('Enter Valid Geo Latitude'));
    }
    
    if(!empty($node->venue_geo_long) && !preg_match('/^(-?(180|(\d|\d\d|1[0-7]\d)(\.\d{1,6}){0,1}))$/', $node->venue_geo_long)) {
        form_set_error('venue_geo_long', t('Enter Valid Geo Longitude'));
    }
}

?>