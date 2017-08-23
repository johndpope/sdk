//
//  PHLivePhotoView.h
//  PhotosUI
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/Photos.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PHLivePhotoViewDelegate;

typedef NS_OPTIONS(NSUInteger, PHLivePhotoBadgeOptions) {
    PHLivePhotoBadgeOptionsOverContent  = 1 << 0,               ///< Include treatments so this image can be shown directly over the content of the Live Photo
    PHLivePhotoBadgeOptionsLiveOff      = 1 << 1,               ///< To indicate that the Live Photo aspect is turned off and it will be treated as a still (e.g. for sharing)
} NS_ENUM_AVAILABLE_IOS(9_1);

typedef NS_ENUM(NSInteger, PHLivePhotoViewPlaybackStyle) {
    PHLivePhotoViewPlaybackStyleUndefined = 0,
    PHLivePhotoViewPlaybackStyleFull,
    PHLivePhotoViewPlaybackStyleHint,
} NS_ENUM_AVAILABLE_IOS(9_1);

NS_CLASS_AVAILABLE_IOS(9_1)
@interface PHLivePhotoView : UIView

/// System badge images representing Live Photo content
+ (UIImage *)livePhotoBadgeImageWithOptions:(PHLivePhotoBadgeOptions)badgeOptions;

@property (readwrite, nonatomic, weak, nullable) id<PHLivePhotoViewDelegate> delegate;

/// Live photo displayed in the receiver.
@property (readwrite, nonatomic, strong, nullable) PHLivePhoto *livePhoto;

/// Indicates whether the audio of the Live Photo is muted.
@property (readwrite, nonatomic, assign, getter=isMuted) BOOL muted;

/// Gesture used to trigger playback. By default, added to the receiver. Can be moved to a different view.
@property (readonly, nonatomic, strong) UIGestureRecognizer *playbackGestureRecognizer;

// The following methods allow the client to manually trigger playback. If the live photo is changed during playback, it will be immediately interrupted.
- (void)startPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;
- (void)stopPlayback;

@end


@protocol PHLivePhotoViewDelegate <NSObject>
@optional

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView willBeginPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView didEndPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

@end


NS_ASSUME_NONNULL_END
