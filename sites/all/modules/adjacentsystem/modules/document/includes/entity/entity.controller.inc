<?php 

class DocumentController extends EntityCRUD {
    public function readEntity($entity_id) {
        $entity = parent::readEntity($entity_id);
        $entity->getDocumentBody();
        return $entity;
    }
}

?>