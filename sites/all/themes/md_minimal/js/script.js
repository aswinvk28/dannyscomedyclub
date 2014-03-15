var GLOBAL = GLOBAL || {};

jQuery.fn.superSimpleTabs = function (conf) {
    var config = jQuery.extend({
            selected:	1, 				// Which tab is initially selected (hash overrides this)
            show:		'show', 		// Show animation
            hide:		'hide', 		// Hide animation
            duration:	0,				// Animation duration
            callback:	function () {}	// Callback after tab has been clicked
    }, conf);

    return this.each(function () {
            var ul	= jQuery(this);
            var ipl	= 'a[href^="#"]';

            // Go through all the in-page links in the ul
            // and hide all but the selected's contents
            ul.find(ipl).each(function (i) {
                    var link = jQuery(this);

                    if ((i + 1) === config.selected) {
                            link.addClass('selected');
                            jQuery(link.parents('li')[0]).addClass('selected');
                    }
                    else {
                            jQuery(link.attr('href')).hide();
                    }
            });

            // When clicking the UL (or anything within)
            ul.click(function (e) {
                    var clicked	= jQuery(e.target);
                    var link	= false;

                    if (clicked.is(ipl)) {
                            link = clicked;
                    }
                    else {
                            var parent = clicked.parents(ipl);

                            if (parent.length) {
                                    link = parent;
                            }
                    }

                    // Only continue if the clicked element was an in page link
                    if (link) {
                            var selected = ul.find('a.selected');

                            if (selected.length) {
                                    ul.find('li.selected').removeClass('selected');
                                    // Remove currently .selected, hide the element it was pointing to
                                    jQuery(selected.removeClass('selected').attr('href'))[config.hide](config.duration, function () {
                                            // Then show the element the clicked link was pointing to
                                            jQuery(link.attr('href'))[config.show](config.duration, function () {
                                                    config.callback(link.attr('href'));
                                            });
                                    });

                                    link.addClass('selected');
                                    jQuery(link.parents('li')[0]).addClass('selected');
                            }
                            else {
                                    jQuery(link.addClass('selected').attr('href'))[config.show](config.duration, function () {
                                            config.callback(link.attr('href'));
                                    });
                            }

                            // Update the hash
                            superSimpleTabsUpdateHash(link.attr('href'));

                            return false;
                    }
            });

            // If a hash is set, click that tab
            var hash = window.location.hash;

            if (hash) {
                    // We can't simply .click() the link since that will run the show/hide animation
                    jQuery(ul.find('a').removeClass('selected').attr('href')).hide();
                    jQuery(ul.find('a[href="' + hash + '"]').addClass('selected').attr('href')).show();
                    config.callback(hash);
            }
    });
};

// http://stackoverflow.com/questions/1489624/modifying-document-location-hash-without-page-scrolling#answer-1489802
function superSimpleTabsUpdateHash (hash) {
	hash = hash.replace( /^#/, '' );
	var fx, node = $( '#' + hash );
	if ( node.length ) {
	  fx = $( '<div></div>' )
		      .css({
		          position:'fixed',
		          left:0,
		          top:0,
		          visibility:'hidden'
		      })
		      .attr( 'id', hash )
		      .appendTo( document.body );
	  node.attr( 'id', '' );
	}
	document.location.hash = hash;
	if ( node.length ) {
	  fx.remove();
	  node.attr( 'id', hash );
	}
}

(function ($) {
    $.fn.extend({

        akordeon: function (options) {
            var settings = $.extend({ expandedItem: 0, expandSpeed: 200, toggle: false, expandText: '&ndash;', collapseText: '+', buttons: true, hiddenItem: -1, itemsOrder: [] }, options);
            return this.each(function () {

                var expandedItem = settings.expandedItem;
                var speed = settings.expandSpeed;
                var expandText = settings.expandText;
                var collapseText = settings.collapseText;
                var isToggle = settings.toggle;

                var akordeon = $(this);
                if (!akordeon.hasClass('akordeon'))
                    akordeon.addClass('akordeon');

                if (settings.itemsOrder != null && settings.itemsOrder != undefined && settings.itemsOrder.length > 0) {
                    if (settings.itemsOrder.length != akordeon.find('.akordeon-item').length) {
                        alert('Parameter value mismatch with total items');
                    }
                    else {
                        var items = akordeon.find('.akordeon-item').clone(true);
                        akordeon.find('.akordeon-item').remove();

                        $(settings.itemsOrder).each(function () {
                            akordeon.append(items.eq(this));
                        });
                    }
                }
                $('.akordeon-item', akordeon).each(function () {
                    var body = $(this).find('.akordeon-item-body');
                    var h = body.outerHeight();
                    body.data('h', h);
                    $(this).find('.akordeon-item-head').addClass('akordeon-border-bottom');
                    body.addClass('akordeon-border-bottom');
                    if (settings.buttons)
                        $(this).find('.akordeon-item-head-container').prepend('<div class="akordeon-icon"><span>' + collapseText + '</span></div>');
                });
                if (settings.hiddentItem > -1) {
                    var hiddenItem = $('.akordeon-item', akordeon).eq(settings.hiddenItem).hide();

                    hiddenItem.find('.akordeon-item-head', akordeon).last().removeClass('akordeon-border-bottom');
                    hiddenItem.find('.akordeon-item-body', akordeon).last().removeClass('akordeon-border-bottom');
                }
                $('.akordeon-item .akordeon-item-head', akordeon).last().removeClass('akordeon-border-bottom');
                $('.akordeon-item .akordeon-item-body', akordeon).last().removeClass('akordeon-border-bottom');
                $('.akordeon-item:first').addClass('akordeon-item-first');
                $('.akordeon-item:last').addClass('akordeon-item-last');
                $('.akordeon-item', akordeon).removeClass('expanded').addClass('collapsed');
                $('.akordeon-item.collapsed .akordeon-item-body', akordeon).css({ height: 0 });
                expandItem($('.akordeon-item', akordeon).eq(expandedItem));

                $('.akordeon-item-head-container', akordeon).click(function () {
                    var currentItem = $(this).parents('.akordeon-item');
                    var previousItem = akordeon.find('.akordeon-item.expanded');
                    var isExpanded = currentItem.hasClass('expanded');
                    if (!isToggle) {
                        if (!isExpanded) {
                            collapseItem(previousItem);
                            expandItem(currentItem);
                        }
                    }
                    else {
                        if (isExpanded)
                            collapseItem(currentItem);
                        else
                            expandItem(currentItem);
                    }
                });

                function expandItem(item) {
                    var body = item.find('.akordeon-item-body');
                    var h = body.data('h');
                    body.animate({ height: h }, speed, function () {
                        item.removeClass('collapsed').addClass('expanded').find('.akordeon-icon span').html(expandText);
                    });
                }
                function collapseItem(item) {
                    var body = item.find('.akordeon-item-body');
                    body.animate({ height: 0 }, speed, function () {
                        item.removeClass('expanded').addClass('collapsed').find('.akordeon-icon span').html(collapseText);
                    });
                }
            });
        }
    });
})(jQuery);

(function ($) {

    if( $.isFunction($.fn.superSimpleTabs) ) {
        $tabs = $('.js_tabs');
        $tabs.superSimpleTabs({ duration: 300, show: 'fadeIn', hide: 'fadeOut' });
    }

    if( $.isFunction($.fn.tooltip) ) {
        $('.bootstrap_title').tooltip({
            placement: 'bottom',
            delay: { show: 200, hide: 100 },
            trigger: 'hover'
        });
    }

    if( $.browser.msie && !!window.PIE ) {
        if( $.browser.version < 8 ) {
            $('.box_shadow').each(function() {
                PIE.attach(this);
            });
        }
        if ( $.browser.version < 9 ) {
            $('.border_radius_large, .border_radius, .border_radius_small, .stage-shows li .label, .js-pane, .js_tabs li').each(function() {
                PIE.attach(this);
            });
        }
    }

    if( $('#map_container').length > 0 && !!google ) {
        window.mapInitialize = function() {
            var latlng = new google.maps.LatLng(new Number($('#map_lat').text()).valueOf(), new Number($('#map_long').text()).valueOf());
            var mapOptions = {
                center: latlng,
                zoom: 16,
                mapTypeId: google.maps.MapTypeId.ROADMAP
            };

            var map = new google.maps.Map(document.getElementById("map_container"), mapOptions);
            new google.maps.Marker({
                map: map,
                position: mapOptions.center
            });

        };

        google.maps.event.addDomListener(window, 'load', mapInitialize);
    }


    if($.isFunction($.fn.colorbox)) {
        var colorbox = function() {};
        colorbox.prototype.onYouTubeIframeAPIReady = function(element, width, height) {
            object = document.createElement('object');
            $(object).addClass('iframe_video').css({ 'display': 'block', 'width': width, 'height': height });
            param = document.createElement('param');
            $(param).attr('name', 'movie').attr('value', 'http://www.youtube.com/v/' + element.data('href') + '?version=3&autoplay=1&wmode=opaque');
            embed = document.createElement('embed');
            $(embed).attr('src', 'http://www.youtube.com/v/' + element.data('href') + '?version=3&autoplay=1&wmode=opaque').attr('type', "application/x-shockwave-flash").attr('allowscriptaccess', "always").css({ 'display': 'block', 'width': '100%', 'height': '100%' });
            $(object).append(param).append(embed);
            return object;
        };
        $('.colorbox-video').colorbox({
            html: '<span>Content Loading...</span>',
            speed: 100,
            width: '938px',
            height: '528px',
            maxWidth: '100%',
            maxHeight: '100%',
            rel: 'video',
            current: '<span>Video <span class="label label-info">{current}</span> of <span class="label label-info">{total}</span></span>. <span>Use arrow keys to navigate</span>',
            onComplete: function () {
                $('#cboxLoadedContent :first-child').hide();
                $('#cboxLoadedContent').css('padding', '20px').append(colorbox.onYouTubeIframeAPIReady($(this), '892', '488'));
            }
        });
        $('.colorbox-image').colorbox({
            maxWidth: '100%',
            maxHeight: '100%',
            rel: 'image',
            speed: 100,
            current: '<span>Image <span class="label label-info">{current}</span> of <span class="label label-info">{total}</span></span>. <span>Use arrow keys to navigate</span>'
        });
        $('.page-video').click(function() {
            $('#pageVideoIframe').append(colorbox.onYouTubeIframeAPIReady($(this), '100%', '432'));
            $(this).hide();
            return false;
        });
        colorbox = new colorbox();
    }
    
    if($('#club-audio').length > 0) {
        $('#club-audio').jPlayer({
            swfPath: "/sites/default/packages/jQuery.jPlayer.2.4.0/jQuery.jPlayer.2.4.0/Jplayer.swf",
            ready: function () {
                $(this).jPlayer("setMedia", {
                    mp3: "/sites/default/files/resources/Dannys_Comedy_Club_MERIFM.mp3"
                });
            }
            
        });
    }
    
    $('.share-trigger').bind('click', function() {
        var scripts = document.getElementsByTagName("script");
        var newScript = document.createElement("script");
        newScript.src = "http://s7.addthis.com/js/300/addthis_widget.js#pubid=ra-517427cf23e21205";
        $(newScript).attr('type', 'text/javascript');
        $(scripts[scripts.length - 1]).after(newScript);
        $(this).unbind('click');
        $('.share-links').show();
        $(this).hide();
    });
    
    GLOBAL.masonry = function(length) {
        var elements = []; this.length = length; var obj = this, current_last = false;
        var iterator = function(index, element) {
            elements.push(element);
            current_last = ( (( index + 1 ) % obj.length) === 0 );
            if( index === 0 ) {
                obj.count = $(element).siblings().not('.row-fluid.decolumn_mini').length + 1;
            }
            if( current_last || (!current_last && (( index + 1 ) === obj.count)) || (!current_last && (obj.count < obj.length)) ) {
                $(elements).wrapAll('<div class="row-fluid decolumn_mini"/>');
                elements = [];
            }
        };
        var setLength = function(length) {
            obj.length = length;
        };
        this.iterator = iterator;
        this.setLength = setLength;
    };
    
    if($('#artistes-masonry').length > 0 || $('.performances-masonry').length > 0 || $('.performance-clips-masonry').length > 0 || $('.performers-masonry').length > 0) {
    	masonry = new GLOBAL.masonry(4);
    	$('#artistes-masonry > .span3').each(masonry.iterator);
    	$('.performances-masonry > .span3').each(masonry.iterator);
        $('.performers-masonry > .span3').each(masonry.iterator);
        $('.performance-clips-masonry > .span3').each(masonry.iterator);
        $('.show-highlights-masonry > .span3').each(masonry.iterator);
        masonry.setLength(6);
        $('.performers-masonry > .span2').each(masonry.iterator);
        masonry.setLength(2);
        $('.performers-masonry > .span6').each(masonry.iterator);
    }
    
})(jQuery);

var addthis_config = { "data_track_addressbar": true };

/* Backbone Routing and Ajax */

if(!!window.Backbone) {

    (function ($, Backbone) {

        var LoadingView = Backbone.View.extend({
            tagName: 'div',
            className: 'modal-backdrop',
            imageSrc: '/sites/all/themes/md_minimal/images/ajax-load/108.gif',
            initialize: function() {
                var view = this;
                $(this.el).html('<div style="width:100%;height:100%" class="align-center"><span style="position:relative;top:50%;margin-top:-200px;color:white"><img src="' + view.imageSrc + '"/></span></div>');
            }
        });
        
        GLOBAL.loading = function(toLoad) {
            var loadingView = new LoadingView();
            if(toLoad) {
                $('body.body-patternbg').append(loadingView.el);
            } else {
                $('.' + loadingView.className).remove();
            }
        }
        
        var AppRouter = Backbone.Router.extend({
            routes: {
                "!/page/:num": "listPageResults",
            },

            listPageResults: function (page) {
                $('#status-messages').html('').hide();
                if($('#page-list-items-ajax').length !== 0) {
                    page = new Number(page);
                    $('#performer-page-ajax').hide();
                    $('#page-list-items-ajax').hide();
                    var page_count = new Number($('#paginator_page_count').text());
                    this.collection = new PerformerCollection({
                        page: page,
                        page_count: page_count
                    });
                    $('#paginator_description #paginator_page_number').text(page);
                    if(page <= page_count) {
                        if(page < page_count) {
                            $('#paginator_next a').attr('href', '#/!/page/' + (page + 1)).attr('class', 'active bootstrap_title');
                        } else {
                            $('#paginator_next a').attr('href', '#').attr('class', 'disabled');
                        }
                        if(page > 1) {
                            $('#paginator_previous a').attr('href', '#/!/page/' + (page - 1)).attr('class', 'active bootstrap_title');
                        } else {
                            $('#paginator_previous a').attr('href', '#').attr('class', 'disabled');
                        } 
                    } else {
                        $('#paginator_next a').attr('href', '#').attr('class', 'disabled');
                    }
                    if($('#paginator_select').val() != page) {
                        $('#paginator_select').val(page);
                    }
                }
            }
        });

        var PerformerCollection = Backbone.Collection.extend({
            initialize: function(options) {
                var page = options.page;
                var context = this;
                this.url = "/performer/page/" + page;
                if(page > options.page_count) {
                    this.errorPage();
                    return this;
                }
                GLOBAL.loading(true);
                this.fetch({
                    success: function(collection, resp) {
                        var data = $.parseJSON(resp[1]['data']);
                        $('#performer-page-ajax').show();
                        $('#page-list-items-ajax').show();
                        if(!data) {
                            context.errorPage();
                            return this;
                        }
                        var performersView = new PerformerPageListView({collection: data});
                        $('#page-list-items-ajax').html(performersView.el);
                        masonry = new GLOBAL.masonry(6);
                        $('.performers-masonry > .span2').each(masonry.iterator);
                    },
                    error : function(xhr, textStatus, errorThrown) {
                        context.errorPage();
                        return this;
                    },
                    complete: function(xhr, textStatus) {
                        GLOBAL.loading(false);
                    }
                });
                return this;
            },
            errorPage: function() {
                var bootstrapAlert = new BootstrapAlert({
                    message : 'Requested Resource Not Found',
                    type: 'Warning'
                });
                $('#status-messages').html(bootstrapAlert.el).show();
            }
        });

        var BootstrapAlert = Backbone.View.extend({
            initialize: function(options) {
                var view = this;
                $(this.el).html(view.render({
                    message: options.message,
                    type: options.type
                }));
                return this;
            },
            tagName: 'div',
            'className': 'alert clearfix column_small decolumn_small',
            template: '<button type=\"button\" class=\"close\" data-dismiss=\"alert\">&times;</button><strong><%= type %>!</strong> <%= message %>',
            render: function(options) {
                var func = _.template(this.template);
                return func(options);
            }
        });

        var PerformerPageListView = Backbone.View.extend({
            tagName: 'div',
            className: 'row-fluid performers-masonry',
            initialize: function(options) {
                _.each(this.collection, function(value, key) {
                    this.model = {
                        path: value.link_url,
                        title: value.title,
                        image: '<img src="'+ value.image +'" />'
                    };
                    var performerView = new PerformerView({ model: this.model });
                    $(this.el).append(performerView.el);
                }, this);
                return this;
            }
        });

        var PerformerView = Backbone.View.extend({
            tagName: 'div',
            'className': 'span2 align-center decolumn_small',
            template: '<h5><a href=\"<%= model.path %>\" class="white underline"><%= model.title %></a></h5> \
               <div class="column_mini"><a class="clearfix" href=\"<%= model.path %>\"><%= model.image %></a></div>',
            render: function(options) {
                var func = _.template(this.template);
                return func(options);
            },
            initialize: function(options) {
                var model = this.model;
                var view = this;
                $(this.el).append(view.render({
                    model: model
                }));
                return this;
            }
        });

        var Domain = new AppRouter();
        Backbone.history.start();

        $('#paginator_select').change(function(event) {
            Domain.listPageResults($(this).val());
            event.preventDefault();
        });
        
    })(window.jQuery, window.Backbone ? window.Backbone : undefined);
    
}