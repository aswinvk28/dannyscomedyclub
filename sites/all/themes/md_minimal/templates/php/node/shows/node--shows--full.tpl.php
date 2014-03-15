<div class="clearfix column <?php print $classes; ?>" <?php print $attributes; ?> itemscope itemtype="http://schema.org/Event">
    <article class="row-fluid">
        <div class="span8">
            <div class="clearfix column_small">
                <span class="white">Date:</span>
                <div class="clearfix">
                    <meta itemprop="startDate" value="<?php print $show['date']; ?>" />
                    <?php $date = new DateTime($show['date']);
                    print theme('list_item_view', array(
                        'ul_class' => 'act-tags',
                        'li_class' => 'act-tag pull-left white',
                        'items' => array(
                            array(
                                'content' => $date->format('l\, jS F Y')
                            )
                        )
                    )); ?>
                </div>
            </div>
            <div class="clearfix column_small">
                <span class="white">Venue:</span>
                <div class="clearfix" itemscope itemtype="http://schema.org/EventVenue" itemprop="location">
                    <meta itemprop="name" value="<?php print $venue['title']; ?>" />
                    <meta itemprop="url" value="<?php print $venue['path']; ?>" />
                    <?php print theme('list_item_view', array(
                        'ul_class' => 'act-tags',
                        'li_class' => 'act-tag pull-left white',
                        'items' => array(
                            array(
                                'content' => '<a class="underline" href="'.$venue['path'].'">'.$venue['title'].'</a>'
                            )
                        )
                    )); ?>
                </div>
            </div>
            <?php if(!empty($show['performers'])) { ?>
            <div class="clearfix column">
                <span class="white">Performers:</span>
                <div class="row-fluid column_mini thumbnails performers-masonry">
                    <?php print $show['performers']; ?>
                </div>
            </div>
            <?php }
            if(!empty($content['body'])) {
            if(!empty($show['description'])) { ?>
            <div class="clearfix column">
                <span class="white">About the show:</span>
                <article class="clearfix column_mini">
                    <?php print $show['description']; ?>
                </article>
            </div>
            <?php } else { ?>
            <div class="clearfix column">
                <span class="white">About the show:</span>
                <article class="clearfix column_mini">
                    <?php print drupal_render($content['body']); ?>
                </article>
            </div>
            <?php } } ?>
        </div>
        <?php if(!empty($show['promo']) || !empty($reviews) || !empty($press_releases)) { ?>
        <aside class="span4">
            <div class="row-fluid column_small">
                <?php if(!empty($show['promo'])) { ?>
                <article class="clearfix align-center">
                    <?php print $show['promo']; ?>
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
    <?php if(!empty($show['performances'])) { ?>
    <div class="clearfix column">
        <span class="white">Performances:</span>
        <div class="row-fluid column_mini thumbnails performances-masonry">
            <?php print $show['performances']; ?>
        </div>
    </div>
    <?php }
    if(!empty($show['photos'])) { ?>
    <section class="column clearfix">
        <header class="column_title row">
            <h3>Snaps of the Show:</h3>
        </header>
        <article class="row column_mini performances-masonry">
            <?php print $show['photos']; ?>
        </article>
    </section>
    <?php if(!empty($show['highlights'])) { ?>
    <section class="column clearfix">
        <header class="column_title row">
            <h3>Show Highlights:</h3>
        </header>
        <article class="row column_mini performances-masonry">
            <?php print $show['highlights']; ?>
        </article>
    </section>
    <?php }
    } if(!empty($show['upcoming'])) { ?>
    <section class="column clearfix">
        <header class="column_title row">
            <h3>Upcoming Shows:</h3>
        </header>
        <div class="clearfix column_mini">
            <?php print $show['upcoming']; ?>
        </div>
    </section>
    <?php } if(!empty($show['finished'])) { ?>
    <section class="column clearfix">
        <header class="column_title row">
            <h3>Finished Shows:</h3>
        </header>
        <div class="clearfix column_mini">
            <?php print $show['finished']; ?>
        </div>
    </section>
    <?php } if(!empty($show['future'])) { ?>
    <section class="column clearfix">
        <header class="column_title row">
            <h3>Future Shows:</h3>
        </header>
        <div class="clearfix column_mini">
            <?php print $show['future']; ?>
        </div>
    </section>
    <?php } ?>
</div>