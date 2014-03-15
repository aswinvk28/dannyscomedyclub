<?php 

interface BundleNodeEntityCRUDInterface {
    public function readEntitiesFromBundleNode($entity_id);
}

interface ReferenceNodeEntityCRUDInterface {
    public function readEntitiesFromReferenceNode($entity_id);
}

abstract class BundleNodeEntityCRUD extends ReferralEntityCRUD implements BundleNodeEntityCRUDInterface {
    public function readEntitiesFromBundleNode($entity_id) {
        return $this->readEntitiesFromNode($entity_id, 'bundle');
    }
    
    public function getEntityIdsFromBundleNode($entity_id) {
        return $this->getEntityIdsFromNode($entity_id, 'bundle');
    }
    
    protected function readEntitiesFromNode($entity_id, $bundle = '', $conditions = array()) {
        return $this->readEntities($entity_id, implode('_', array('node', $bundle)), $conditions);
    }
    
    protected function getEntityIdsFromNode($entity_id, $bundle = '', $conditions = array()) {
        return $this->getEntityIds($entity_id, implode('_', array('node', $bundle)), $conditions);
    }
}

abstract class ReferenceNodeEntityCRUD extends ReferralEntityCRUD implements ReferenceNodeEntityCRUDInterface {
    public function readEntitiesFromReferenceNode($entity_id) {
        return $this->readEntitiesFromNode($entity_id, 'reference');
    }
    
    protected function readEntitiesFromNode($entity_id, $bundle = '', $conditions = array()) {
        return $this->readEntities($entity_id, implode('_', array('node', $bundle)), $conditions);
    }
    
    protected function getEntityIdsFromNode($entity_id, $bundle = '', $conditions = array()) {
        return $this->getEntityIds($entity_id, implode('_', array('node', $bundle)), $conditions);
    }
}

abstract class BundleReferenceNodeEntityCRUD extends BundleNodeEntityCRUD implements BundleNodeEntityCRUDInterface, ReferenceNodeEntityCRUDInterface {
    public function readEntitiesFromReferenceNode($entity_id) {
        return $this->readEntitiesFromNode($entity_id, 'reference');
    }
}

if(!class_exists('NodeEntity')) :

class NodeEntity extends CommonEntity {
    var $nid;
    var $type;
    protected $node;
    protected $title;
    private $fetched;
    
    function getNode() {
        if(empty($this->node)) {
            $this->node = node_load($this->nid);
            $this->title = $this->node->title;
            $this->type = $this->node->type;
        }
        return $this->node;
    }
    
    function getType() {
        return $this->type;
    }
    
    function getTitle() {
        return $this->title;
    }
    
    function initialize() {
        if(empty($this->fetched)) {
            $this->fetched = $this->getEntityField(array($this->entityInfo['entity keys']['label'], $this->entityInfo['entity keys']['bundle']));
            if(!empty($this->fetched)) {
                list($this->title, $this->type) = array_values((array) $this->fetched);
            }
        }
        return $this;
    }
}

endif;

if(!class_exists('CoreNodeView')) :

interface CoreNodeViewInterface {
    public function getEntity();
}

abstract class CoreNodeView {

    protected $entity;
    protected $performances = array();

    function setPerformances($performance_instances) {
        $this->performances = $performance_instances;
    }
    
    function viewPerformances($view_mode = 'photos_view') {
        $performance_entities = $this->getPublishedPerformances();
        if(!empty($performance_entities)) {
            $method = 'filter_performances_' . $view_mode . '_' . get_class(current($performance_entities));
            return $this->{$method}();
        } else {
            return "<p>Watch this space! Details of danny's artistes will be updated.</p>";
        }
    }
    
    protected function filter_performances_photos_view_PerformanceEntity() {
        $performance_entities = $this->getPublishedPerformances();
        $view = array('photos' => '');
        foreach($performance_entities  as $performance_entity) {
            $performance = new PerformanceNodeView($performance_entity->getPerformance());
            $performance->setEntity($performance_entity);
            $view['photos'] .= $performance->viewPhotos();
        }
        return $view;
    }
    
}
	
endif;

?>