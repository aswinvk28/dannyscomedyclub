<div class="clearfix column <?php print $classes; ?>" <?php print $attributes; ?> itemscope itemtype="http://schema.org/"<?php print $itemType; ?>>
    <h3 class="white">
        <span itemprop="performer" itemscope itemtype="http://schema.org/Person">
            <a itemprop="url" href="<?php print $performer['path']; ?>"><span itemprop="name"><?php print $performer['title']; ?></span></a>
        </span> in 
        <span itemprop="superEvent" itemscope itemtype="http://schema.org/Event">
            <a itemprop="url" href="<?php print $show['path']; ?>"><span itemprop="name"><?php print $show['title']; ?></span></a>
        </span> at 
        <?php print variable_get('site_name', "Danny's Comedy Club"); ?>
    </h3>
    
    <section class="row-fluid">
        <div class="span8">
            <aside class="align-center column_small">
                <div class="row-fluid">
                    <?php if(!empty($performance_video)) { ?>
                    <aside class="span7">
                        <?php print $performance_video; ?>
                    </aside>
                    <?php }
                    if(!empty($performance_promo)) { ?>
                    <aside class="span5">
                        <?php print $performance_promo; ?>
                    </aside>
                    <?php } ?>
                </div>
            </aside>
            <div class="clearfix column_small">
                <span class="white">Performer:</span>
                <div class="clearfix">
                <?php print theme('list_item_view', array(
                    'ul_class' => 'act-tags',
                    'li_class' => 'act-tag pull-left white',
                    'items' => array(
                        array(
                            'content' => '<a class="underline" href="'.$performer['path'].'">'.$performer['title'].'</a>'
                        )
                    )
                )); ?>
                </div>
            </div>
            <div class="clearfix column_small">
                <span class="white">Date:</span>
                <div class="clearfix">
                <?php print theme('list_item_view', array(
                    'ul_class' => 'act-tags',
                    'li_class' => 'act-tag pull-left white',
                    'items' => array(
                        array(
                            'content' => $performance_date
                        )
                    )
                )); ?>
                </div>
            </div>
            <div class="clearfix column_small">
                <span class="white">Show:</span>
                <div class="clearfix">
                <?php print theme('list_item_view', array(
                    'ul_class' => 'act-tags',
                    'li_class' => 'act-tag pull-left white',
                    'items' => array(
                        array(
                            'content' => '<a class="underline" href="'.$show['path'].'">'.$show['title'].'</a>'
                        )
                    )
                )); ?>
                </div>
            </div>
            <div class="clearfix column_small">
                <span class="white">Venue for the Show:</span>
                <div class="clearfix">
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
            
            <?php 
            if(!empty($content['body'])) { ?>
            <article class="clearfix column_small">
                <span class="white">About:</span>
                <div class="clearfix">
                    <?php print drupal_render($content['body']); ?>
                </div>
                <div class="clearfix">
                    <?php print $performance_quotes; ?>
                </div>
            </article>
            <?php } ?>
        </div>
        <?php if(!empty($reviews) || !empty($press_releases)) { ?>
        <aside class="span4">
            <?php if(!empty($reviews)) { ?>
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
        </aside>
        <?php } ?>
    </section>
    
    <?php if(!empty($photos)): ?>
    <section class="row-fluid column">
        <header class="column_title row">
            <h3>Performances:</h3>
        </header>
        <div class="row column_mini performances-masonry">
            <?php print $photos; ?>
        </div>
    </section>
    <?php endif; 
    if(!empty($co_performances)) { ?>
    <section class="row-fluid column">
        <header class="column_title row">
            <h3>Co-Performances at the Show:</h3>
        </header>
        <article class="row column_mini performances-masonry">
            <?php print $co_performances; ?>
        </article>
    </section>
    <?php }
    if(!empty($co_performers)) { ?>
    <section class="row-fluid column">
        <header class="column_title row">
            <h3>Co-Performers at the Show:</h3>
        </header>
        <article class="row column_mini performers-masonry">
            <?php print $co_performers; ?>
        </article>
    </section>
    <?php } ?>
</div>