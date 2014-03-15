<?php

class PerformanceEntity extends CommonEntity {
    var $performance_order;
    var $entity_node_bundle_id;
    var $entity_node_shows_id;
    var $entity_performer_id;
    var $entity_event_id;
    var $performance_video;
    var $entity_taxonomy_performances_types_id;
    var $node_type = 'performances';
    private $event;
    private $bundle_node;
    private $bundle_entity;
    private $show_entity;
    private $performer_entity;
    
    public function getParentEntity() {
        if(empty($this->event)) {
            $this->event = entity_get_controller('event')->readEntity($this->getEvent());
        }
        return $this->event;
    }
    
    public function getEvent() {
        return $this->entity_event_id;
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
    
    public function getShow() {
        return $this->entity_node_shows_id;
    }
    
    public function getShowEntity() {
        if(empty($this->show_entity)) {
            $entity = entity_get_controller('show')->readMultipleEntities(array(), array(
                'entity_node_bundle_id' => $this->getShow()
            ));
            $this->show_entity = current($entity);
        }
        return $this->show_entity;
    }
    
    public function getPerformer() {
        return $this->entity_performer_id;
    }
    
    function getPublishedPerformances() {
        return NULL;
    }
    
    public function getPerformerEntity() {
        if(empty($this->performer_entity)) {
            $this->performer_entity = entity_load_single('performer', $this->getPerformer());
        }
        return $this->performer_entity;
    }
    
    public function getPerformanceType() {
        return $this->entity_taxonomy_performances_types_id;
    }
    
    public function getOrder() {
        return $this->performance_order;
    }
    
    public function getVideo() {
        return $this->performance_video;
    }
    
    public function getYtVideoId() {
        return str_replace('http://www.youtube.com/watch?v=', '', $this->getVideo());
    }
}

?>