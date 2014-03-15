<div class="clearfix column" itemtype="http://schema.org/Person" itemscope>
    <article class="row-fluid">
        <div class="span8">
            <?php if(!empty($performance_type)) { ?>
            <div class="clearfix column_small">
                <p>At Danny's Comedy Club, <?php print $performer['title']; ?></p>
                <div class="row-fluid">
                    <span class="white">Performs:</span>
                    <div class="clearfix">
                        <?php print $performance_type; ?>
                    </div>
                </div>
            </div>
            <?php } if(!empty($appeared_performances)) {?>
            <div class="clearfix column_small">
                <span class="white">Has Appeared In:</span>
                <div class="row-fluid column_mini thumbnails">
                    <?php
                    
                    
                        foreach($appeared_performances as $appeared_performance) { ?>

                        <div class="span4 label-success thumbnail">
                        <?php $uri = entity_uri('show', $appeared_performance->getShowEntity());
                        $venue_uri = entity_uri('show', $appeared_performance->getShowEntity()->getVenueEntity());
                        $date = new DateTime($appeared_performance->getShowEntity()->getParentEntity()->getDate());
                        $performance_uri = entity_uri('performance', $appeared_performance);
                        print theme('list_item_view', array(
                            'ul_class' => 'clearfix unstyled image_text',
                            'li_class' => 'column_mini',
                            'items' => array(
                                array(
                                    'content' => '<span class="black">Performance: </span><span><a class="underline" href="'. url($performance_uri['path'], array('base_url' => TRUE)) .'" class="read-more black">'.entity_label('performance', $appeared_performance).'</a></span>'
                                ),
                                array(
                                    'content' => '<span class="black">Show: </span><span><a class="underline" href="'. url($uri['path'], array('base_url' => TRUE)) .'" class="read-more black">'.entity_label('show', $appeared_performance->getShowEntity()).'</a></span>'
                                ),
                                array(
                                    'content' => '<span class="black">Date: </span><span class="white">'.$date->format('l\, jS F Y').'</span>'
                                ),
                                array(
                                    'content' => '<span class="black">Venue: </span><span><a class="underline" href="'. url($venue_uri['path'], array('base_url' => TRUE)) .'" class="read-more black">'.entity_label('venue', $appeared_performance->getShowEntity()->getVenueEntity()).'</a></span>'
                                )
                            )
                        ));
                        ?>
                        </div>
                        <?php } 
                    ?>
                </div>
            </div>
            <?php } if(!empty($booked_performances)) { ?>
            <div class="clearfix column_small">
                <span class="white">Has been Booked For:</span>
                <div class="row-fluid column_mini thumbnails">
                    <?php
                    
                        foreach($booked_performances as $booked_performance) { ?>

                        <div class="span4 label-info thumbnail">
                        <?php $uri = entity_uri('show', $booked_performance->getShowEntity());
                        $venue_uri = entity_uri('show', $booked_performance->getShowEntity()->getVenueEntity());
                        $date = new DateTime($booked_performance->getShowEntity()->getParentEntity()->getDate());
                        $performance_uri = entity_uri('performance', $booked_performance);
                        print theme('list_item_view', array(
                            'ul_class' => 'clearfix unstyled image_text',
                            'li_class' => 'column_mini',
                            'items' => array(
                                array(
                                    'content' => '<span class="black">Performance: </span><span><a class="underline" href="'. url($performance_uri['path'], array('base_url' => TRUE)) .'" class="read-more black">'.entity_label('performance', $booked_performance).'</a></span>'
                                ),
                                array(
                                    'content' => '<span class="black">Show: </span><span><a class="underline" href="'. url($uri['path'], array('base_url' => TRUE)) .'" class="read-more black">'.entity_label('show', $booked_performance->getShowEntity()).'</a></span>'
                                ),
                                array(
                                    'content' => '<span class="black">Date: </span><span class="white">'.$date->format('l\, jS F Y').'</span>'
                                ),
                                array(
                                    'content' => '<span class="black">Venue: </span><span><a class="underline" href="'. url($venue_uri['path'], array('base_url' => TRUE)) .'" class="read-more black">'.entity_label('venue', $booked_performance->getShowEntity()->getVenueEntity()).'</a></span>'
                                )
                            )
                        ));
                        ?>
                        </div>
                        <?php }
                    ?>
                </div>
            </div>
            <?php } ?>
            <div class="clearfix column">
                <span class="white">About <?php print $performer['title']; ?>:</span>
                <meta itemprop="name" value="<?php print $performer['title']; ?>" />
                <meta itemprop="url" value="<?php print $performer['path']; ?>" />
                <article class="row-fluid column_mini">
                    <aside class="span4">
                        <?php print $performer_image; ?>
                    </aside>
                    <div class="span8">
                        <div class="clearfix">
                            <?php 
                            if(!empty($content['body'])) {
                                if(!empty($description)) {
                                    print $description;
                                } else {
                                    print drupal_render($content['body']);
                                }
                            } ?>
                        </div>
                        <div class="clearfix column_small">
                            <?php print render($performer_press_quotes); ?>
                        </div>
                    </div>
                </article>
                <?php if(!empty($performer_extra_images)) { ?>
                <div class="row-fluid column_mini performers-masonry">
                    <?php print $performer_extra_images; ?>
                </div>
                <?php } if(!empty($performer['website'])) { ?>
                <p><i><a class="underline" itemprop="sameAs" href="<?php print $performer['website']; ?>">Read More About <?php print $performer['title']; ?></a></i></p>
                <?php } ?>
            </div>
        </div>
        <?php if(!empty($show_promo) || !empty($reviews) || !empty($press_releases)) { ?>
        <aside class="span4">
            <div class="row-fluid column_small">
                <?php if(!empty($show_promo)) { ?>
                <article class="clearfix align-center">
                    <?php print $show_promo; ?>
                </article>
                <?php } if(!empty($reviews)) { ?>
                <header class="column_title column_small">
                    <h3>Reviews:</h3>
                </header>
                <div class="clearfix column_mini">
                    <?php print $reviews; ?>
                </div>
                <?php } if(!empty($press_releases)) { ?>
                <header class="column_title column_small">
                    <h3>Press Releases:</h3>
                </header>
                <div class="clearfix column_mini">
                    <?php print $press_releases; ?>
                </div>
                <?php } ?>
            </div>
        </aside>
        <?php } ?>
    </article>
    <?php if(!empty($photos)) { ?>
    <section class="row-fluid column">
        <header class="column_title row">
            <h3>Performances:</h3>
        </header>
        <article class="row column_mini performances-masonry">
            <?php print $photos; ?>
        </article>
    </section>
    <?php }
    if(!empty($co_performers)) { ?>
    <section class="row-fluid column">
        <header class="column_title row">
            <h3>Co-Performers at the Danny's Comedy Club:</h3>
        </header>
        <article class="row column_mini performers-masonry">
            <?php print $co_performers; ?>
        </article>
    </section>
    <?php } ?>
</div>