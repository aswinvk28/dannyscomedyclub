<?php

class VenueController extends BundleNodeEntityCRUD implements BundleNodeEntityCRUDInterface {
    protected function buildQuery($ids, &$conditions = array(), $revision_id = FALSE, &$node_conditions = array()) {
        $query = parent::buildQuery($ids, $conditions);
        if(array_key_exists('node.status', $node_conditions) && isset($node_conditions['node.status'])) {
            if(($node_conditions['node.status'] == 0 || $node_conditions['node.status'] == 1)) {
                $query->innerJoin('node', 'n', 'n.nid='.$this->entity_alias.'.entity_node_bundle_id');
                $query->condition('n.status', $node_conditions['node.status']);
            }
            unset($node_conditions['node.status']);
        }
        $fields = &$query->getFields();
        unset($fields['venue_address']);
        unset($fields['venue_location']);
        unset($fields['venue_telephone']);
        unset($fields['venue_geo_lat']);
        unset($fields['venue_geo_long']);
        
        return $query;
    }
}

?>