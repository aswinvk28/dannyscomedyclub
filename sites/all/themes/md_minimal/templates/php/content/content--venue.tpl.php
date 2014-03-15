<?php

$venues = entity_get_controller('venue')->readMultipleEntities(array(), array(), array(
    'node.status' => 1
));

if(!empty($venues)) { ?>

    <section class="akordeon column_small">
        <div class="akordeon-item">
            <?php $venue_view = entity_view('venue', $venues, 'list_view');
            print drupal_render($venue_view); ?>
        </div>
    </section>

<?php } ?>