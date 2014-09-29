<?php 

$date_interval = DannysComedyClubDotCom::getCurrentAndNextYear();
$context_shows = entity_get_controller('show')->readMultipleEntities(array(), array(), array(
    'node.status' => 1,
    'node.promote' => 1,
    'event_date' => array(
        'after' => $date_interval['after'],
        'before' => $date_interval['before']
    )
));
$upcoming_shows = array_filter($context_shows, function($entity) {
    return taxonomy_term_load($entity->getParentEntity()->getEventStatus())->name == 'Upcoming';
});
$rest_shows = array_diff_key($context_shows, $upcoming_shows);
$finished_shows = array_filter($rest_shows, function($entity) {
    return taxonomy_term_load($entity->getParentEntity()->getEventStatus())->name == 'Finished';
});
$rest_shows = array_diff_key($context_shows, $finished_shows);
$confirmed_shows = array_filter($rest_shows, function($entity) {
    return taxonomy_term_load($entity->getParentEntity()->getEventStatus())->name == 'Confirmed';
});

$context_shows = array_merge($upcoming_shows, $finished_shows, $confirmed_shows, array_diff_key($rest_shows, $confirmed_shows));

if( !empty( $context_shows ) ) { ?>

    <section class="akordeon column_small">
        <div class="akordeon-item">
            <?php $show_view = entity_view('show', $context_shows, 'front_page');
            print drupal_render($show_view); ?>
        </div>
    </section>

<?php } ?>