<?php

class ShowEntity extends CommonEntity {
    var $entity_node_bundle_id;
    var $entity_node_venue_id;
    var $entity_event_id;
    var $node_title;
    var $node_type = 'shows';
    private $event;
    private $bundle_node;
    private $bundle_entity;
    private $performances;
    private $venue_entity;
    
    public function getParentEntity() {
        if(empty($this->event)) {
            $this->event = entity_get_controller('event')->readEntity($this->getEvent());
        }
        return $this->event;
    }
    
    public function getBundle() {
        return $this->entity_node_bundle_id;
    }
    
    public function getBundleNode() {
        if(empty($this->bundle_node)) {
            $this->bundle_node = node_load($this->getBundle());
        }
        return $this->bundle_node;
    }
    
    public function getBundleTitle() {
        $node = $this->bundle_node;
        if(empty($this->bundle_node)) {
            if(!is_null($this->node_title)) {
                return $this->node_title;
            }
            $entity = $this->getBundleEntity();
            $entity->initialize();
            return (!empty($entity) && !is_null($entity->getTitle())) ? $entity->getTitle() : '';
        }
        return (!empty($node) && property_exists($node, 'title')) ? $node->title : '';
    }
    
    public function getBundleEntity() {
        if(empty($this->bundle_entity)) {
            $this->bundle_entity = new NodeEntity(array(
                'nid' => $this->getBundle(),
                'type' => $this->node_type
            ), 'node');
        }
        return $this->bundle_entity;
    }
    
    public function getVenue() {
        return $this->entity_node_venue_id;
    }
    
    public function getVenueEntity() {
        if(empty($this->venue_entity)) {
            $entity = entity_get_controller('venue')->readMultipleEntities(array(), array(
                'entity_node_bundle_id' => $this->getVenue()
            ));
            $this->venue_entity = current($entity);
        }
        return $this->venue_entity;
    }
    
    public function getEvent() {
        return $this->entity_event_id;
    }
    
    public function getPublishedPerformances() {
        if(empty($this->performances)) {
            $this->performances = entity_get_controller('performance')->readMultipleEntities(array(), array(
                'entity_node_shows_id' => $this->getBundle()
            ), array(
                'node.status' => 1
            ));
        }
        return $this->performances;
    }
}

?>