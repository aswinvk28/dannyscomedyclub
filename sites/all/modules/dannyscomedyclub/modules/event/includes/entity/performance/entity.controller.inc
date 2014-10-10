<?php 

class PerformanceController extends BundleNodeEntityCRUD implements BundleNodeEntityCRUDInterface {
    
    public function buildQuery($ids, $conditions = array(), $revision_id = FALSE, &$node_conditions = array()) {
        $query = parent::buildQuery($ids, $conditions);
        $subQuery = clone $query;
        if(array_key_exists('node.status', $node_conditions) && isset($node_conditions['node.status'])) {
            if(($node_conditions['node.status'] == 0 || $node_conditions['node.status'] == 1)) {
                $query->innerJoin('node', 'n', 'n.nid='.$this->entity_alias.'.entity_node_bundle_id');
                $query->condition('n.status', $node_conditions['node.status']);
                $query->orderBy($this->entity_alias.'.performance_order', 'ASC');
            }
            unset($node_conditions['node.status']);
        }
        return $query;
    }
    
    public function setNewActs(array $performances) {
        foreach($performances as $performance_entity) {
            $performance_entities = $performance_entity->getPerformerEntity()->getPublishedPerformances();
            $performance_entity->setNew(count($performance_entities));
        }
        return $performances;
    }
    
}

?>