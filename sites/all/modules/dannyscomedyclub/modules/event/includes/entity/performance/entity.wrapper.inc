<?php

class PerformanceEntityWrapper {
    public static function data($values) {
        return array(
            'entity_node_shows_id' => !empty($values['entity_node_shows_id']) ? $values['entity_node_shows_id'] : NULL,
            'entity_performer_id' => !empty($values['entity_performer_id']) ? $values['entity_performer_id'] : NULL,
            'entity_taxonomy_performances_types_id' => !empty($values['entity_taxonomy_performances_types_id']) ? $values['entity_taxonomy_performances_types_id'] : NULL,
            'performance_order' => !empty($values['performance_order']) ? $values['performance_order'] : NULL,
            'performance_video' => !empty($values['performance_video']) ? $values['performance_video'] : NULL
        );
    }
}

?>