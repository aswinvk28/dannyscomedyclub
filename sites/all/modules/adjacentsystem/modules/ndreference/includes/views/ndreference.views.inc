<?php

function review_review__review__full(&$vars) {
    $entity = $vars['elements']['#entity'];
    $reference_uri = dannyscomedyclub_uri($entity->getNodeReferenceEntity());
    
    $vars['review'] = array(
        'name' => $entity->getName(),
        'reference_path' => url($reference_uri['path'], array('base_url' => TRUE)),
        'reference_title' => $entity->getNodeReferenceEntity()->getTitle(),
        'description' => $entity->getParentEntity()->getDocumentBody(),
        'author' => $entity->getParentEntity()->getAuthor()
    );
    
    $date_value = $entity->getDate();
    if(!empty($date_value)) {
        $date = new DateTIme($entity->getDate());
        $vars['review']['date'] = $date->format('l, d F Y');
    }
}

function press_release_press_release__press_release__full(&$vars) {
    $entity = $vars['elements']['#entity'];
    $reference_uri = dannyscomedyclub_uri($entity->getNodeReferenceEntity());
    
    $vars['press_release'] = array(
        'name' => $entity->getName(),
        'reference_path' => url($reference_uri['path'], array('base_url' => TRUE)),
        'reference_title' => $entity->getNodeReferenceEntity()->getTitle(),
        'description' => $entity->getParentEntity()->getDocumentBody(),
        'author' => $entity->getParentEntity()->getAuthor()
    );
    
    $date_value = $entity->getDate();
    if(!empty($date_value)) {
        $date = new DateTIme($entity->getDate());
        $vars['press_release']['date'] = $date->format('l, d F Y');
    }
}

?>