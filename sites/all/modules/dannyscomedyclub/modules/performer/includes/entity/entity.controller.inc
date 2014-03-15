<?php

class PerformerController extends BundleNodeEntityCRUD implements BundleNodeEntityCRUDInterface {
    
    protected function buildQuery($ids, &$conditions = array(), $revision_id = FALSE, &$node_conditions = array()) {
        $query = parent::buildQuery($ids, $conditions);
        $fields =& $query->getFields();
        unset($fields['performer_email']);
        unset($fields['performer_website']);
        unset($fields['performer_fb']);
        unset($fields['performer_twitter']);
        unset($fields['performer_yt']);
        unset($fields['performer_opt']);
        if(array_key_exists('node.status', $node_conditions) && isset($node_conditions['node.status'])) {
            if(($node_conditions['node.status'] == 0 || $node_conditions['node.status'] == 1)) {
                $query->innerJoin('node', 'n', 'n.nid='.$this->entity_alias.'.entity_node_bundle_id');
                $query->condition('n.status', $node_conditions['node.status']);
                if(!empty($node_conditions['performer.range'])) {
                    $query->range($node_conditions['performer.range']['start'], $node_conditions['performer.range']['length']);
                    $query->orderBy('n.changed', 'DESC');
                    unset($node_conditions['performer.range']);
                }
            }
            unset($node_conditions['node.status']);
        }
        return $query;
    }
    
}

?>