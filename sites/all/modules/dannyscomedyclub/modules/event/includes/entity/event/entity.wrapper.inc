<?php

class EventEntityWrapper {
    public static function data($values) {
        return array(
            'event_name' => !empty($values['event_name']) ? $values['event_name'] : NULL,
            'event_url' => !empty($values['event_url']) ? $values['event_url'] : NULL,
            'image_caption' => !empty($values['image_caption']) ? $values['image_caption'] : NULL,
            'event_image_file_id' => !empty($values['event_image_file_id']) ? $values['event_image_file_id'] : NULL,
            'event_image_event_id' => !empty($values['event_image_event_id']) ? $values['event_image_event_id'] : NULL,
            'entity_taxonomy_event_status_id' => !empty($values['entity_taxonomy_event_status_id']) ? $values['entity_taxonomy_event_status_id'] : NULL,
            'event_date' => !empty($values['event_date']) ? $values['event_date'] : NULL
        );
    }
}

?>