<?php 

$date_interval = DannysComedyClubDotCom::getCurrentAndNextYear();
$context_shows = entity_get_controller('show')->readMultipleEntities(array(), array(), array(
    'node.status' => 1,
    'event_date' => array(
        'after' => $date_interval['after'],
        'before' => $date_interval['before']
    )
));

if( !empty( $context_shows ) ):

    $shows_result = array();

    foreach($context_shows as $entity_id => $entity) {
        $date = new DateTime($entity->getParentEntity()->getDate());
        $shows_result[(int) $date->format('Y')][$entity_id] = $entity;
    }
    
    if(!empty($shows_result)) {
    
        krsort($shows_result, SORT_NUMERIC);
    
        foreach($shows_result as $year => $shows) : ?>

        <div class="column_title column_small">
            <h4>Danny's <?php echo $year; ?> Season</h4>
        </div>
        <ul id="shows-progress" class="unstyled clearfix stage-shows">

        <?php foreach( $shows as $show ): 

            $show_entity_view = new ShowEntityView($show);
            $uri = entity_uri('show', $show);

            print theme('shows_progress_view', array(
                'show_status' => $show_entity_view->printStatus(),
                'show_class' => $show_entity_view->printClass(),
                'title' => entity_label('show', $show),
                'uri_path' => $uri['path'],
                'attributes' => drupal_attributes(array(
                    'itemscope' => '',
                    'itemtype' => 'http://schema.org/Event'
                ))
            ));

            endforeach; ?>
        </ul>

        <?php endforeach;
    }
endif; ?>