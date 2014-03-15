<?php 

abstract class EntityCRUD extends EntityAPIController {
    protected $entity_alias = 'base';
    
    public function loadEntity($ids = array(), $conditions = array(), $additional_conditions = array()) {
        if(!is_array($ids)) return NULL;
        $query = $this->buildQuery($ids, $conditions, FALSE, $additional_conditions);
        return $query->execute()->fetchAllAssoc($this->idKey);
    }
    
    public function readEntity($entity_id, $conditions = array()) {
        $entities = $this->loadEntity(array($entity_id), $conditions);
        return entity_get_controller($this->entityType)->create((array) reset($entities));
    }
    
    public function readMultipleEntities($ids, $conditions, $additional_conditions = array()) {
        $entities = $this->loadEntity($ids, $conditions, $additional_conditions);
        foreach($entities as $entity_id => $entity) {
            $entities[$entity_id] = entity_get_controller($this->entityType)->create((array) $entity);
        }
        return $entities;
    }
    
    public function getEntityInfo() {
        return $this->entityInfo;
    }
    
    public function getEntityBundles() {
        $bundles = array();
        foreach($this->entityInfo['bundles'] as $key => $bundle) {
            $bundles[$key] = $bundle['label'];
        }
        return $bundles;
    }
}

abstract class ReferralEntityCRUD extends EntityCRUD {
    
    protected function readEntities($ref_entity_id, $entity = NULL, $conditions = array()) {
        if(is_null($entity)) return NULL;
        $ids = $this->getEntityIds($ref_entity_id, implode('_', array('entity', $entity)), $conditions);
        if(!empty($ids)) {
            $entities = $this->readMultipleEntities(array_keys($ids), $conditions);
            return $entities;
        }
        return $ids;
    }
    
    protected function getEntityIds($ref_entity_id, $entity = NULL, $conditions = array()) {
        if(is_null($entity)) return NULL;
        if(!is_array($ref_entity_id)) {
            $ref_entity_id = array($ref_entity_id);
        }
        $query = db_select($this->entityInfo['base table'], $this->entity_alias)->fields($this->entity_alias, array($this->idKey))
                ->condition($this->entity_alias.'.'.$entity .'_id', $ref_entity_id, 'IN');
        if(!empty($conditions['range']) && gettype($conditions['range']) == 'integer') {
            $query->range(0, $conditions['range']);
        }
        return $query->execute()->fetchAllAssoc($this->idKey);
    }
}

abstract class ReferralDerivedEntityCRUD extends ReferralEntityCRUD {
    public function readEntity($entity_id, $conditions = array()) {
        $entity = parent::readEntity($entity_id, $conditions);
        $entity->getParentEntity();
        return $entity;
    }
}

abstract class CommonEntity extends Entity {
    protected $entity_alias = 'base';
    
    public function getEntityId() {
        return entity_id($this->entityType, $this);
    }
    
    protected function getEntityField($field) {
        if(!is_array($field)) {
            $field = array($field);
        }
        $query = db_select($this->entityInfo['base table'], $this->entity_alias)->fields(
                $this->entity_alias,
                    $field
                )->condition($this->entity_alias.'.'.$this->idKey, $this->getEntityId());
        $obj = $query->execute()->fetchObject();
        return $obj;
    }
}

//class EntityFactory {
//    private static $instance = array();
//
//    public static function getEntityInstancesFromBundleNode($entityType, $entity_id) {
//        if(!isset(self::$instance[$entityType]['bundle'][$entity_id])) {
//            self::$instance[$entityType]['bundle'][$entity_id] = entity_get_controller($entityType)->readEntitiesFromBundleNode($entity_id);
//        }
//        return self::$instance[$entityType]['bundle'][$entity_id];
//    }
//    
//    public static function getEntityInstancesFromReferenceNode($entityType, $entity_id) {
//        if(!isset(self::$instance[$entityType]['reference'][$entity_id])) {
//            self::$instance[$entityType]['reference'][$entity_id] = entity_get_controller($entityType)->readEntitiesFromReferenceNode($entity_id);
//        }
//        return self::$instance[$entityType]['reference'][$entity_id];
//    }
//}

?>