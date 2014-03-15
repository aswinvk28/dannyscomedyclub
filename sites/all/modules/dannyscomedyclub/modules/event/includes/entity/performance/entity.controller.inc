<?php 

class PerformanceController extends BundleNodeEntityCRUD implements BundleNodeEntityCRUDInterface {
    
    public function buildQuery($ids, $conditions = array(), $revision_id = FALSE, &$node_conditions = array()) {
        $query = parent::buildQuery($ids, $conditions);
        if(array_key_exists('node.status', $node_conditions) && isset($node_conditions['node.status'])) {
            if(($node_conditions['node.status'] == 0 || $node_conditions['node.status'] == 1)) {
                $query->innerJoin('node', 'n', 'n.nid='.$this->entity_alias.'.entity_node_bundle_id');
                $query->condition('n.status', $node_conditions['node.status']);
            }
            unset($node_conditions['node.status']);
        }
        return $query;
    }
    
}

?>