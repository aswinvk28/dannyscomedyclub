<?php 
if(!empty($review)) {
    $entityInfo = entity_get_info($entityType);
    foreach($review as $entity_id => $body) {
        if(gettype($entity_id) == 'integer') { ?>
        <article class="clearfix column_small">
        <?php 
            print theme('hover_block', array(
                'body' => $body,
                'performer' => NULL,
                'uri_path' => url(key($entityInfo['bundles']).'/'.$entity_id, array('base_path' => true)),
                'link_title' => 'View the '.$entityInfo['label']
            )); ?>
        </article>
        <?php 
        } else { 
            foreach($review as $performer => $item) { 
                if(!empty($item)) {
                foreach($item as $entity_id => $body) { ?>
                    <article class="clearfix column_small">
                    <?php 
                        print theme('hover_block', array(
                            'performer' => $performer,
                            'body' => $body,
                            'uri_path' => url(key($entityInfo['bundles']).'/'.$entity_id, array('base_path' => true)),
                            'link_title' => 'View the '.$entityInfo['label']
                        ));
                    } ?>
                    </article>
            <?php } } }
    }
}
 ?>