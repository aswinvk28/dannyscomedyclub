<?php

class EventEntity extends CommonEntity {
    var $event_id;
    var $image_caption;
    var $event_bundle;
    var $event_image_event_id;
    var $event_image_file_id;
    var $event_url;
    var $event_name;
    var $entity_taxonomy_event_status_id;
    var $event_date;
    private $image;
    private $bundle_entity;
    
    public function getImageCaption() {
        return $this->image_caption;
    }
    
    public function getPromoEvent() {
        return $this->event_image_event_id;
    }
    
    public function getEventImage() {
        return $this->event_image_file_id;
    }
    
    public function getBundleString() {
        return $this->event_bundle;
    }
    
    public function getBundleEntity() {
        if(empty($this->bundle_entity) && !is_null($this->getBundleString())) {
            $entities = entity_load($this->getBundleString(), FALSE, array(
                'entity_event_id' => $this->getEntityId()
            ));
            $this->bundle_entity = current($entities);
        }
        return $this->bundle_entity;
    }
    
    public function setBundleEntity($entity) {
        $this->bundle_entity = $entity;
    }
    
    public function getBundleTitle() {
        return !empty($this->event_name) ? $this->event_name : !is_null($this->getBundleEntity()) ? $this->getBundleEntity()->getBundleTitle() : '';
    }
    
    public function getImage() {
        if(empty($this->image)) {
            $this->image = $this->getEntityField(array('event_image_file_id', 'event_image_event_id', 'image_caption'));
            if(!empty($this->image)) {
                list($this->event_image_file_id, $this->event_image_event_id, $this->image_caption) = array_values((array) $this->image);
            }
        }
        return $this->image;
    }
    
    public function getUrl() {
        return $this->event_url;
    }
    
    public function getName() {
        return $this->event_name;
    }
    
    public function getEventStatus() {
        return $this->entity_taxonomy_event_status_id;
    }
    
    public function setEventStatus($term_id) {
        $this->entity_taxonomy_event_status_id = $term_id;
    }
    
    public function getDate() {
        return $this->event_date;
    }
    
}

?>