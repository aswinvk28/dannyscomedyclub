<?php 

class ShowController extends BundleNodeEntityCRUD implements BundleNodeEntityCRUDInterface {
    public function buildQuery($ids, &$conditions = array(), $revision_id = FALSE, &$node_conditions = array()) {
        $query = parent::buildQuery($ids, $conditions);
        if(array_key_exists('node.status', $node_conditions) && isset($node_conditions['node.status'])) {
            if(($node_conditions['node.status'] == 0 || $node_conditions['node.status'] == 1)) {
                $query->innerJoin('node', 'n', 'n.nid='.$this->entity_alias.'.entity_node_bundle_id');
                $query->condition('n.status', $node_conditions['node.status']);
                $query->addField('n', 'title', 'node_title');
                $query->addField('n', 'type', 'node_type');
                if(array_key_exists('node.promote', $node_conditions) && ($node_conditions['node.promote'] == 0 || $node_conditions['node.promote'] == 1)) {
                    $query->condition('n.promote', $node_conditions['node.promote']);
                    unset($node_conditions['node.promote']);
                }
                if(is_array($node_conditions['event_date']) && !empty($node_conditions['event_date'])) {
                    $event_info = entity_get_info('event');
                    $query->innerJoin($event_info['base table'], 'event', 'event.event_id='.$this->entity_alias.'.entity_event_id');
                    $query->condition('event.event_date', $node_conditions['event_date']['after'], '>=');
                    $query->condition('event.event_date', $node_conditions['event_date']['before'], '<=');
                    $query->orderBy('event.event_date', 'DESC');
                    unset($node_conditions['event_date']);
                }
            }
            unset($node_conditions['node.status']);
        }
        
        return $query;
    }
}

?>