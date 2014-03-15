<?php

class VenueEntityWrapper {
    public function data($values) {
        return array(
            'venue_address' => !empty($values['venue_address']) ? $values['venue_address'] : NULL,
            'venue_location' => !empty($values['venue_location']) ? $values['venue_location'] : NULL,
            'venue_telephone' => !empty($values['venue_telephone']) ? $values['venue_telephone'] : NULL,
            'venue_geo_lat' => !empty($values['venue_geo_lat']) ? $values['venue_geo_lat'] : NULL,
            'venue_geo_long' => !empty($values['venue_geo_long']) ? $values['venue_geo_long'] : NULL,
            'venue_url' => !empty($values['venue_url']) ? $values['venue_url'] : NULL,
            'document_body' => !empty($values['document_body']) ? $values['document_body'] : NULL,
            'document_author' => NULL
        );
    }
}

?>