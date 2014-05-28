<?php

function artistes_content_form($node, &$form_state) {
    $form = array();
    PerformerCRUD::performer_node_form($form, $form_state, $node);
    return $form;
}

function artistes_content_validate($node) {
    
    if(module_exists('pressquotation')) {
        module_invoke('pressquotation', 'formfields_node_validate', $node);
    }
    
    if(!empty($node->performer_email) && !preg_match('/^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$/', $node->performer_email)) {
        form_set_error('performer_email', 'Enter Valid Email Address');
    }
    
    if(!empty($node->performer_fb) && !preg_match('/^http[s]?:\/\/(www|[a-zA-Z]{2}-[a-zA-Z]{2})\.facebook\.com\/([a-z]+\/[a-zA-Z0-9\.-]+(\/[0-9]+|[a-zA-Z0-9\.-]+)?)[\/]?$/', $node->performer_fb)) {
        form_set_error('performer_fb', 'Enter Valid FB Page');
    }
    
    if(!empty($node->performer_twitter) && !preg_match('/^http[s]?:\/\/(www\.)?twitter\.com\/(#!\/)?[a-zA-Z0-9]{1,15}[\/]?$/', $node->performer_twitter)) {
        form_set_error('performer_twitter', 'Enter Valid Twitter Page');
    }
    
    if(!empty($node->performer_yt) && !preg_match('/^http:\/\/\w{0,3}.?youtube+\.\w{2,3}\/watch\?v=[\w-]{11}/', $node->performer_yt)) {
        form_set_error('performer_yt', 'Enter Valid Youtube Link');
    }
    
    if(!empty($node->performer_website) && !preg_match('/\b([\d\w\.\/\+\-\?\:]*)((ht|f)tp(s|)\:\/\/|[\d\d\d|\d\d]\.[\d\d\d|\d\d]\.|www\.|\.tv|\.ac|\.com|\.edu|\.gov|\.int|\.mil|\.net|\.org|\.biz|\.info|\.name|\.pro|\.museum|\.co)([\d\w\.\/\%\+\-\=\&amp;\?\:\\\&quot;\'\,\|\~\;]*)\b/', 
            $node->performer_website)) {
        form_set_error('performer_website', 'Enter valid Website URL');
    }
    
}

?>