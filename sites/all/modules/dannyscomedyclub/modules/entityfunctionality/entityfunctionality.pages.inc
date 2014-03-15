<?php

function dannyscomedyclub_entitytitle($entity) {
    if(is_object($entity)) {
        $info = $entity->entityInfo();
        $title = $info['label'].' : '.entity_label($entity->entityType(), $entity);
        drupal_set_title($title);
        return $title;
    }
}

function dannyscomedyclub_entityview($entity, $view_mode) {
    return is_object($entity) ? $entity->view($view_mode) : FALSE;
}

?>