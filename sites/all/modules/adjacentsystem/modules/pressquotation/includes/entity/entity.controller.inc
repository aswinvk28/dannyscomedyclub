<?php

class QuoteController extends ReferenceNodeEntityCRUD implements ReferenceNodeEntityCRUDInterface {
    protected function buildQuery($ids, $conditions = array(), $revision_id = FALSE, $range_conditions = array()) {
        $query = parent::buildQuery($ids, $conditions);
        $fields = & $query->getFields();
        unset($fields['quote']);
        unset($fields['quote_date']);
        if(isset($range_conditions['quote.range']) && gettype($range_conditions['quote.range']) == 'integer') {
            $query->range(0, $range_conditions['quote.range']);
            unset($range_conditions['quote.range']);
        }
        return $query;
    }
}

?>