<?php 

class NodeDocumentReferenceEntityWrapper {
    public static function data($values) {
        return array(
            'ndreference_name' => !empty($values['ndreference_name']) ? $values['ndreference_name'] : NULL,
            'entity_taxonomy_agency_id' => !empty($values['entity_taxonomy_agency_id']) ? $values['entity_taxonomy_agency_id'] : NULL,
            'document_body' => !empty($values['document_body']) ? $values['document_body'] : NULL,
            'document_author' => !empty($values['document_author']) ? $values['document_author'] : NULL,
            'ndreference_date' => !empty($values['ndreference_date']) ? $values['ndreference_date'] : NULL,
            'entity_node_reference_id' => !empty($values['entity_node_reference_id']) ? $values['entity_node_reference_id'] : NULL,
            'ndreference_bundle' => !empty($values['ndreference_bundle']) ? $values['ndreference_bundle'] : NULL
        );
    }
}

?>