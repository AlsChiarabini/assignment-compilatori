; ModuleID = 'test4.ll'
source_filename = "test4.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

; Function Attrs: mustprogress noinline norecurse nounwind ssp uwtable
define noundef i32 @main() #0 {
  %1 = mul nsw i32 2, 1
  br label %2

2:                                                ; preds = %6, %0
  %.0 = phi i32 [ 0, %0 ], [ %5, %6 ]
  %3 = mul nsw i32 2, 1
  %4 = mul nsw i32 %3, 3
  %5 = add nsw i32 %.0, 1
  br label %6

6:                                                ; preds = %2
  %7 = icmp slt i32 %5, 10
  br i1 %7, label %2, label %8, !llvm.loop !6

8:                                                ; preds = %6
  %9 = mul nsw i32 %3, 10
  %10 = mul nsw i32 %3, 12
  ret i32 0
}

attributes #0 = { mustprogress noinline norecurse nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 4]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Homebrew clang version 20.1.3"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
