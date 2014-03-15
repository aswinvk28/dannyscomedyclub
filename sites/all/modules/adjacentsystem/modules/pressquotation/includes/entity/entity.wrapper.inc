<?php

class QuoteEntityWrapper {
    public static function data($values) {
        return array(
            'entity_taxonomy_agency_id' => !empty($values['entity_taxonomy_agency_id']) ? $values['entity_taxonomy_agency_id']: NULL,
            'entity_taxonomy_author_id' => !empty($values['entity_taxonomy_author_id']) ? $values['entity_taxonomy_author_id'] : NULL,
            'quote' => !empty($values['quote']) ? $values['quote'] : NULL,
            'quote_date' => !empty($values['quote_date']) ? $values['quote_date'] : NULL
        );
    }
}

?>